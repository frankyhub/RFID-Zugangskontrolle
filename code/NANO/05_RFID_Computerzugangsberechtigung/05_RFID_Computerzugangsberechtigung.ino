/*************************************************************************************************
                                      PROGRAMMINFO
**************************************************************************************************
Funktion: Computerzugangsberechtigung

**************************************************************************************************
Version: 12.11.2022
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
// import libraries
#include <SPI.h>
#include <MFRC522.h>

#include <Adafruit_NeoPixel.h>

const uint8_t RST_PIN = 9; // reset pin
const uint8_t SS_PIN = 10; // serial data pin

const uint8_t UID_LENGTH = 4, UID_COUNT = 2;

const uint8_t UNLOCK_PIN = 2;

const uint8_t RGB_LED_COUNT = 8;

const uint8_t PERMITTED_UIDS[UID_COUNT][UID_LENGTH] = {
  { 0xB5, 0xA3, 0x2B, 0x1B },
  { 0x3A, 0x06, 0xE8, 0xAB }
};

MFRC522 mfrc522(SS_PIN, RST_PIN); // create MFRC522 instance

Adafruit_NeoPixel light = Adafruit_NeoPixel(RGB_LED_COUNT, 4, NEO_GRB + NEO_KHZ800);

void setup() {
  digitalWrite(UNLOCK_PIN, LOW);
  pinMode(UNLOCK_PIN, OUTPUT);
  
  Serial.begin(9600); // start serial connection
  SPI.begin(); // start SPI bus
  mfrc522.PCD_Init(); // init RFID module
  light.begin(); // initialize NeoPixel library
}

void loop() {
  setOutputColor(15, 15, 15);
  
  // listen for new cards and read data
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    setOutputColor(200, 200, 0);

    // check uid size
    if (mfrc522.uid.size != UID_LENGTH) {
      Serial.println("UID length missmatch");
    }
    else if (isPermitted(mfrc522.uid.uidByte)) {
      Serial.println("Unlocked");
      setOutputColor(0, 255, 0);
      //digitalWrite(UNLOCK_PIN, HIGH);
      delay(500);
      digitalWrite(UNLOCK_PIN, LOW);
      delay(1500);
    }
    else {
      Serial.println("Locked");
      setOutputColor(255, 0, 0);
      delay(1000);
    }
    
    mfrc522.PICC_HaltA();
  }
}

bool isPermitted(uint8_t *uid) {
  for (uint16_t uidIndex = 0; uidIndex < UID_COUNT; uidIndex++) {
    bool match = true;
    for (uint8_t byteIndex = 0; byteIndex < UID_LENGTH; byteIndex++) {
      Serial.print(PERMITTED_UIDS[uidIndex][byteIndex], HEX);
      Serial.println(uid[byteIndex], HEX);
      if (PERMITTED_UIDS[uidIndex][byteIndex] != uid[byteIndex]) {
        match = false;
      }
    }
    if (match) return true;
  }
  return false;
}

void setOutputColor(byte r, byte g, byte b) {
  for (int i = 0; i < RGB_LED_COUNT; i++) {
    light.setPixelColor(i, light.Color(r, g, b));
  }
  light.show();
}
