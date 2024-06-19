/*************************************************************************************************
                                      PROGRAMMINFO
**************************************************************************************************
Funktion: RFID Mini Alarmanlage
https://draeger-it.blog/arduino-projekt-alarmanlage-mit-rfid-steuerung/
**************************************************************************************************
Version: 21.06.2022
**************************************************************************************************
Board: NANO
**************************************************************************************************
Libraries:
https://github.com/espressif/arduino-esp32/tree/master/libraries
C:\Users\User\Documents\Arduino
D:\gittemp\Arduino II\A156_Wetterdaten_V3
**************************************************************************************************
C++ Arduino IDE V1.8.19

**************************************************************************************************
Einstellungen:
https://dl.espressif.com/dl/package_esp32_index.json
http://dan.drown.org/stm32duino/package_STM32duino_index.json
http://arduino.esp8266.com/stable/package_esp8266com_index.json
**************************************************************************************************/
#include <SPI.h>
#include <RFID.h>

#define SS_PIN 10
#define RST_PIN 9

int ledStatusPin = 2; // Status LED Gruen an digitalen PIN 2
int ledAktivPin = 3; // Aktiv LED Rot an digitalen PIN 3
int buzzerPin = 4; // Buzzer an digitalen PIN 4
int relaisPin = 5; // Relais an digitalen PIN 5 (HIGH == deaktiviert & LOW == aktiviert)
int alarmPin = 6; // Schalter fuer Alarm an digitalen PIN 6

boolean isActive = false;
boolean isAlarm = false;

RFID rfid(SS_PIN, RST_PIN);

String ids[2] = {"453B56D16", "8C3B3924AA1"}; //Zugelassene ID's

void setup()
{
  pinMode(ledStatusPin, OUTPUT);
  pinMode(ledAktivPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(relaisPin, OUTPUT);

  pinMode(alarmPin, INPUT);

  digitalWrite(alarmPin, HIGH);

  Serial.begin(9600);
  SPI.begin();
  rfid.init();
}

void loop() {
  if (isActive) {
    //Wenn die Alarmanlage aktiviert ist dann soll die rote LED aufleuchten.
    digitalWrite(ledAktivPin, HIGH);
    //Wenn kein Alarm aktiviert ist, so soll der Status des Alarmpins ausgewertet werden.
    if (isAlarm == false) {
      isAlarm = digitalRead(alarmPin) == HIGH;
    }
  } else {
    //Wenn die Alarmanlage deaktiviert ist, dann soll die rote LED aus sein und das Relais soll abgefallen sein.
    digitalWrite(ledAktivPin, LOW);
    digitalWrite(relaisPin, HIGH);
  }

  //Wenn die Alarmanlage an ist und es besteht ein Alarm so soll das Relais angezogen werden.
  if ((isActive == true) && (isAlarm == true)) {
    digitalWrite(relaisPin, LOW);
  } else {
    digitalWrite(relaisPin, HIGH);
  }

  //Wird vor das RFID Modul ein Chip gehalten so wird diese ID ausgelesen.
  if (rfid.isCard() && rfid.readCardSerial()) {
    String serial = parseId(rfid);
    //Ausgabe der ID auf dem Seriellen Monitor
    Serial.println("RFID Nummer: " + serial);

    //Schleife zum pruefen der erkannten RFID.
    int counter = 0;
    boolean foundId = false;
    for (counter = 0; counter < sizeof(ids) - 1; counter++) {
      //Wenn die RFID bekannt ist so soll die Alarmanlage aktiviert bzw. deaktiviert werden.
      if (serial == ids[counter]) {
        isActive = !isActive;
        foundId = true;
        flashLED(ledStatusPin, 250);
        break;
      }
    }

    //Wurde die RFID nicht in den registrierten ID's gefunden,
    //so soll dieses durch das blinken der roten Aktiv LED und
    //dem Buzzer bestätgit werden.
    if (!foundId) {
      flashLED(ledAktivPin, 550);
    } else if (foundId && isAlarm) {
      Serial.println("!!! RFID Nummer wurde gefunden !!!");
      isAlarm = false;
      digitalWrite(relaisPin, HIGH);
    }
  }
  rfid.halt();
  delay(750); //Pause von 750ms
}

//Laesst eine LED am PIN aufblinken,
//der Intervall wird im Parameter milliseconds uebergeben.
void flashLED(int pin, int milliseconds) {
  int i = 0;
  for (i = 0; i < 2; i++) {
    digitalWrite(pin, HIGH);
    tone(buzzerPin, 1050, 350);
    delay(milliseconds);
    digitalWrite(pin, LOW);
    tone(buzzerPin, 1050, 350);
    delay(milliseconds);
  }
}

//Liesst eine ID aus dem Modul
//und gibt diese als String zurueck.
String parseId(RFID rfid) {
  String result = "";
  int position = 0;
  for (position = 0; position <= 4; position++) {
    String pos = getNumPosAsHEX(rfid, position);
    result = result + pos;
  }
  result.toUpperCase();
  return result;
}

//Liefert aus dem Wert des RFID Moduls und einer bestimmten
//Position einen HEXADEZIMAL Codierten Wert zurueck.
String getNumPosAsHEX(RFID rfid, int position) {
  return String(rfid.serNum[position], HEX);
}
