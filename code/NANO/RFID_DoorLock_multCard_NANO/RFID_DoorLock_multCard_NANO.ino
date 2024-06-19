/*************************************************************************************************
                                      PROGRAMMINFO
**************************************************************************************************
Funktion: RFID DoorLock System mult. Card
https://arduinogetstarted.com/tutorials/arduino-rfid-nfc-door-lock-system
**************************************************************************************************
Version: 220.6.2022
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
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
#define RELAY_PIN A5 // the Arduino pin connects to relay

MFRC522 rfid(SS_PIN, RST_PIN);

byte managerKeyUID[4]   = {0x3A, 0xC9, 0x6A, 0xCB};
byte secretaryKeyUID[4] = {0x30, 0x01, 0x8B, 0x15};   

void setup() {
  Serial.begin(9600);
  SPI.begin(); // init SPI bus
  rfid.PCD_Init(); // init MFRC522
  pinMode(RELAY_PIN, OUTPUT); // initialize pin as an output.
  digitalWrite(RELAY_PIN, HIGH); // lock the door

  Serial.println("Tap RFID/NFC Tag on reader");
}

void loop() {
  if (rfid.PICC_IsNewCardPresent()) { // new tag is available
    if (rfid.PICC_ReadCardSerial()) { // NUID has been readed
      MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);

      if (rfid.uid.uidByte[0] == managerKeyUID[0] &&
          rfid.uid.uidByte[1] == managerKeyUID[1] &&
          rfid.uid.uidByte[2] == managerKeyUID[2] &&
          rfid.uid.uidByte[3] == managerKeyUID[3] ) {
        Serial.println("Access is granted for manager");
        digitalWrite(RELAY_PIN, LOW);  // unlock the door for 2 seconds
        delay(2000);
        digitalWrite(RELAY_PIN, HIGH); // lock the door
      }
      else
      if (rfid.uid.uidByte[0] == secretaryKeyUID[0] &&
          rfid.uid.uidByte[1] == secretaryKeyUID[1] &&
          rfid.uid.uidByte[2] == secretaryKeyUID[2] &&
          rfid.uid.uidByte[3] == secretaryKeyUID[3] ) {
        Serial.println("Access is granted for secretary");
        digitalWrite(RELAY_PIN, LOW);  // unlock the door for 2 seconds
        delay(2000);
        digitalWrite(RELAY_PIN, HIGH); // lock the door
      }
      else
      {
        Serial.print("Access denied for user with UID:");
        for (int i = 0; i < rfid.uid.size; i++) {
          Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
          Serial.print(rfid.uid.uidByte[i], HEX);
        }
        Serial.println();
      }

      rfid.PICC_HaltA(); // halt PICC
      rfid.PCD_StopCrypto1(); // stop encryption on PCD
    }
  }
}
