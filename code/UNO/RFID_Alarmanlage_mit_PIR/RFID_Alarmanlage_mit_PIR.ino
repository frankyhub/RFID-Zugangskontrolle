/*************************************************************************************************
                                      PROGRAMMINFO
**************************************************************************************************
Funktion: RFID Alarmanlage mit PIR
https://draeger-it.blog/arduino-projekt-pir-rfid-alarmanlage/
**************************************************************************************************
Version: 21.06.2022
**************************************************************************************************
Board: UNO
**************************************************************************************************
Libraries:
https://github.com/espressif/arduino-esp32/tree/master/libraries
C:\Users\User\Documents\Arduino
D:\gittemp\Arduino II\A156_Wetterdaten_V3
**************************************************************************************************
C++ Arduino IDE V1.8.19

R2-D2
2QK384JVPX
**************************************************************************************************
Einstellungen:
https://dl.espressif.com/dl/package_esp32_index.json
http://dan.drown.org/stm32duino/package_STM32duino_index.json
http://arduino.esp8266.com/stable/package_esp8266com_index.json
**************************************************************************************************/

/*************************************************************************************************
                                      PROGRAMMINFO
**************************************************************************************************
Funktion: 

**************************************************************************************************
Version: 2022
**************************************************************************************************
Board: ESP32vn IoT UNO
**************************************************************************************************
Libraries:
https://github.com/espressif/arduino-esp32/tree/master/libraries
C:\Users\User\Documents\Arduino
D:\gittemp\Arduino II\A156_Wetterdaten_V3
**************************************************************************************************
C++ Arduino IDE V1.8.19

R2-D2
2QK384JVPX
**************************************************************************************************
Einstellungen:
https://dl.espressif.com/dl/package_esp32_index.json
http://dan.drown.org/stm32duino/package_STM32duino_index.json
http://arduino.esp8266.com/stable/package_esp8266com_index.json
**************************************************************************************************/
#include <SPI.h>
#include <RFID.h>

//RGB LED
#define BLUE_LED 7  /* PIN für die blaue LED */
#define RED_LED 4   /* PIN für die rote LED */
#define GREEN_LED 2 /* PIN für die grüne LED */
 
//Piezo Buzzer
#define BUZZER 3 /* PIN für den Buzzer */

//RFID Modul - RC522
#define SS_PIN 10 /* PIN SDA für das RFID Modul */
#define RST_PIN 9 /* PIN RST für das RFID Modul */
RFID rfid(SS_PIN, RST_PIN);
String ids[2] = {"453B56D16", "8C3B3924AA1"}; //Zugelassene ID's

//PIR Modul HC-SR505
#define PIR505_PIN 5 /* PIN OUT für das PIR Modul HC-SR505 */

//PIR Modul HC-SR501
#define PIR501_PIN 6 /* PIN OUT für das PIR Modul HC-SR501 */

boolean isActive = false;

void setup() {
  Serial.begin(9600);

  pinMode(PIR501_PIN, INPUT);
  pinMode(PIR505_PIN, INPUT);

  pinMode(BLUE_LED, OUTPUT);   /* Setzt den PIN für die blaue LED als Ausgang. */
  pinMode(RED_LED, OUTPUT);    /* Setzt den PIN für die rote LED als Ausgang. */
  pinMode(GREEN_LED, OUTPUT);  /* Setzt den PIN für die grüne LED als Ausgang. */

  pinMode(BUZZER, OUTPUT) ; /* Setzt den PIN für den Piezo Buzzer als Ausgang. */

  SPI.begin();
  rfid.init();
}

void loop() {

  boolean foundId = false;
  if (rfid.isCard() && rfid.readCardSerial()) {
    Serial.println("drin");
    String serial = parseId(rfid);
    //Ausgabe der ID auf dem Seriellen Monitor
    Serial.println("RFID Nummer: " + serial);
 
    //Schleife zum pruefen der erkannten RFID.
    int counter = 0;
    for (counter = 0; counter < sizeof(ids) - 1; counter++) {
      //Wenn die RFID bekannt ist so soll die Alarmanlage aktiviert bzw. deaktiviert werden.
      if (serial == ids[counter]) {
        isActive = !isActive;
        foundId = true;
        break;
      }
    }
    Serial.println(foundId);
}

if(isActive){
  blinkActiveLED();
  int pirHC505 = digitalRead(PIR505_PIN);
  int pirHC501 = digitalRead(PIR501_PIN);

  if(pirHC505 == HIGH || pirHC501 == HIGH){
     tone(BUZZER, 500, 50);
     noTone(BUZZER);
  }

}

if(foundId){
    lightUpLED(0, 255, 0);
} else {
    lightUpLED(255, 0, 0);
}
delay(1500);

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

void blinkActiveLED(){
  lightUpLED(0, 0, 255);
  delay(350);
  lightUpLED(0, 0, 0);
  delay(350);
  lightUpLED(0, 0, 255);
  delay(350);
  lightUpLED(0, 0, 0);
}

void lightUpLED(int red, int green, int blue){
  analogWrite(RED_LED, red);
  analogWrite(GREEN_LED, green);
  analogWrite(BLUE_LED, blue );
  
}
