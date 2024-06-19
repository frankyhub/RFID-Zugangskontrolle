/*************************************************************************************************
                                      PROGRAMMINFO
**************************************************************************************************
Funktion: RFID 3 Karten/LEDs ansteuern
https://draeger-it.blog/rfid-kartenleser-rc522-am-arduino-betreiben-update-29-07-2021/
**************************************************************************************************
Version: 21.06.2022
**************************************************************************************************
Board: ESP32 Dev Module
**************************************************************************************************
Libraries:
https://github.com/espressif/arduino-esp32/tree/master/libraries

**************************************************************************************************
C++ Arduino IDE V1.8.19
**************************************************************************************************
Einstellungen:
https://dl.espressif.com/dl/package_esp32_index.json
http://dan.drown.org/stm32duino/package_STM32duino_index.json
http://arduino.esp8266.com/stable/package_esp8266com_index.json
**************************************************************************************************/
#include <SPI.h>
#include <MFRC522.h>

//definieren der Pins  RST & SDA für den ESP32
#define RST_PIN     27
#define SS_PIN      5

#define led1 32
#define led2 33
#define led3 25

bool led1_status = false;
bool led2_status = false;
bool led3_status = false;

MFRC522 rfid(SS_PIN, RST_PIN);

String rfid_nuids[] = {"e9c3 02a4", "c53acb23", "f73f9339"};

void setup() {
  Serial.begin(115200);
  SPI.begin();
  rfid.PCD_Init();

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);

  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
}

void loop() {
  if ( !rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) {
    return;
  }

  String nuid = readHex(rfid.uid.uidByte, rfid.uid.size);
  Serial.println(nuid);

  if (nuid == rfid_nuids[0]) {
    Serial.println("Zugang Karte 1");
    led1_status = !led1_status;
    digitalWrite(led1, led1_status ? HIGH : LOW);
  } else if (nuid == rfid_nuids[1]) {
    Serial.println("Zugang Karte 2");
    led2_status = !led2_status;
    digitalWrite(led2, led2_status ? HIGH : LOW);
  } else if (nuid == rfid_nuids[2]) {
    Serial.println("Zugang Karte 3");
    led3_status = !led3_status;
    digitalWrite(led3, led3_status ? HIGH : LOW);
  }

  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
}

String readHex(byte *buffer, byte bufferSize) {
  String result = "";
  for (byte i = 0; i < bufferSize; i++) {
    String* hex[] = {};
    result = result + String(buffer[i] < 0x10 ? " 0" : "");
    result = result + String(buffer[i], HEX);
  }
  return result;
}
