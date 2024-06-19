/*************************************************************************************************
                                      PROGRAMMINFO
**************************************************************************************************
Funktion: RFID auslesen
https://draeger-it.blog/esp32-mit-rfid-rc522-modul/
**************************************************************************************************
Version: 2022
**************************************************************************************************
Board: ESP32vn IoT UNO
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

//definieren der Pins  RST & SDA für den ESP32
#define RST_PIN     22 //22
#define SS_PIN      21 //21

//erzeugen einer Objektinstanz
MFRC522 mfrc522(SS_PIN, RST_PIN);

//Variable zum speichern der bereits gelesenen RFID-ID
String lastRfid = "";

void setup() {
  //beginn der seriellen Kommunikation mit 115200 Baud
  Serial.begin(115200);
  //eine kleine Pause von 50ms.
  delay(50);
  //begin der SPI Kommunikation
  SPI.begin();
  //initialisieren der Kommunikation mit dem RFID Modul
  mfrc522.PCD_Init();
}

void loop() {
  //Wenn keine neue Karte vorgehalten wurde oder die serielle Kommunikation
  //nicht gegeben ist, dann...
  if ( ! mfrc522.PICC_IsNewCardPresent() || ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  String newRfidId = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    // !! Achtung es wird ein Leerzeichen vor der ID gesetzt !!
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
    Serial.print(" gelesene RFID-ID :");
    Serial.println(newRfidId);
    Serial.println();
  }
}
