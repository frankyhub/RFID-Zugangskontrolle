/*************************************************************************************************
                                      PROGRAMMINFO
**************************************************************************************************
Funktion: RFID LED, Relais ansteuern

**************************************************************************************************
Version: 21.06.2022
**************************************************************************************************
Board: NANO
**************************************************************************************************
Libraries:
https://github.com/miguelbalboa/rfid
https://github.com/espressif/arduino-esp32/tree/master/libraries
**************************************************************************************************
C++ Arduino IDE V1.8.19
**************************************************************************************************
Einstellungen:
https://dl.espressif.com/dl/package_esp32_index.json
http://dan.drown.org/stm32duino/package_STM32duino_index.json
http://arduino.esp8266.com/stable/package_esp8266com_index.json
**************************************************************************************************/
//einbinden der Bibliotheken für das
//ansteuern des MFRC522 Moduls
#include <SPI.h>
#include <MFRC522.h>

//definieren der Pins  RST & SDA für den NANO
#define RST_PIN     9
#define SS_PIN      10

#define ledRot 3
#define ledGruen 2
#define oc_PIN 5 //Open Close PIN

//erzeugen einer Objektinstanz
MFRC522 mfrc522(SS_PIN, RST_PIN);

//Variable zum speichern der bereits gelesenen RFID-ID
String lastRfid = "";

//Anzahl der zulässigen RFID-IDs im Array
const int NUM_RFIDS = 1;
//zulaessige  RFID-ID
String rfids[NUM_RFIDS] = {" 43 7D 3F 92"};

void setup() {
  //beginn der seriellen Kommunikation mit 115200 Baud
  Serial.begin(115200);
  //eine kleine Pause von 50ms.
  delay(50);

  pinMode(ledRot, OUTPUT);
  pinMode(ledGruen, OUTPUT);
  pinMode(oc_PIN, OUTPUT);
  digitalWrite(oc_PIN, LOW);

  //begin der SPI Kommunikation
  SPI.begin();
  //initialisieren der Kommunikation mit dem RFID Modul
  mfrc522.PCD_Init();
}

void loop() {

  //Wenn keine neue Karte vorgehalten wurde oder die serielle Kommunikation
  //nicht gegeben ist, dann...
  if ( !mfrc522.PICC_IsNewCardPresent()) {
    //Serial.println("!PICC_IsNewCardPresent");
    return;
  }

  if (!mfrc522.PICC_ReadCardSerial()) {
    //Serial.println("!PICC_ReadCardSerial");
    return;
  }


  String newRfidId = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    newRfidId.concat(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    newRfidId.concat(String(mfrc522.uid.uidByte[i], HEX));
  }

  //alle Buchstaben in Großbuchstaben umwandeln
  newRfidId.toUpperCase();

  //Wenn die neue gelesene RFID-ID ungleich der bereits zuvor gelesenen ist,
  //dann soll diese auf der seriellen Schnittstelle ausgegeben werden.
  if (!newRfidId.equals(lastRfid)) {
    //überschreiben der alten ID mit der neuen
    lastRfid = newRfidId;
  }


  bool zugangOk = false;
  //prüfen ob die gelesene RFID-ID im Array mit bereits gespeicherten IDs vorhanden ist
  for (int i = 0; i < NUM_RFIDS; i++) {
    //wenn die ID an der Stelle "i" im Array "rfids" mit dem gelesenen übereinstimmt, dann
    if (rfids[i].equals(newRfidId)) {
      zugangOk = true;
      //Schleife verlassen
      break;
    }
  }

  //Wenn die Variable "zugangOk" auf True ist, dann...
  if (zugangOk) {
    digitalWrite(oc_PIN, HIGH); //Türschloss öffnen
    Serial.println("Tuerschloss oeffnen");
    delay(500);
    digitalWrite(oc_PIN, LOW);   
    Serial.println("Tuerschloss schliessen");

    blinkLed(ledGruen);
    Serial.println("RFID-ID [" + newRfidId + "] OK!, Zugang wird gewährt");

    
  } else {
    //Wenn nicht dann...
    blinkLed(ledRot);
    Serial.println("RFID-ID [" + newRfidId + "] nicht OK!, Zugang wird nicht gewährt");
  }

  Serial.println();
}

//Blinken einer LED am Pin "pin"
void blinkLed(int pin) {
  //Schleife von 0 bis 5
  for (int a = 0; a < 5; a++) {
    //LED aktivieren
    digitalWrite(pin, HIGH);
    //eine Pause von 125 ms.
    delay(125);
    //LED deaktivieren
    digitalWrite(pin, LOW);
    //eine Pause von 125 ms.
    delay(125);
  }
}
