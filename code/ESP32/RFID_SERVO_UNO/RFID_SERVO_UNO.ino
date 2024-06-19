/*************************************************************************************************
                                      PROGRAMMINFO
**************************************************************************************************
Funktion: Türöffner mit einem RFID-Modul und Servomotor
WWird die korrekte Karte an das RFID-Modul gehalten, öffnet der Servo­mo­tor die Schranke,
anderenfalls bleibt die Schranke geschlossen. 
Wenn die Karte erneut vor das Leseg­rät gehalten wird, schließt die Schranke wieder.

Zeiterfassung:
https://hartmut-waller.info/arduinoblog/zeiterfassung-mit-rfid-modul/
**************************************************************************************************
Version: 18.10.2022
**************************************************************************************************
Board: ESP32vn IoT UNO
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
// eingebaute Bibliothek einbinden
# include <Servo.h>
// RFID-Bibiothek hinzufügen
# include <MFRC522.h>
// Anschlüsse definieren
# define SDA 10
# define RST 9
// Schranke nach Betreten wieder schließen
bool Status = false;
// RFID-Empfänger benennen
MFRC522 mfrc522(SDA, RST);
// Bezeichnung des Motors
Servo Motor;


void setup()
{
  // Pin des Motors zuordnen
  Motor.attach(7);
  Serial.begin(9600);
  SPI.begin();
  // Initialisierung des RFID-Empfängers
  mfrc522.PCD_Init();
  // Motor in "geschlossen"-Position fahren
  Motor.write(0);
}


void loop()
{
  String WertDEZ;
  // Wenn keine Karte in Reichweite ist ..
  if (!mfrc522.PICC_IsNewCardPresent())
  {
    // .. wird die Abfrage wiederholt.
    return;
  }
  // Wenn kein RFID-Sender ausgewählt wurde ..
  if (!mfrc522.PICC_ReadCardSerial())
  {
    // .. wird die Abfrage wiederholt.
    return;
  }
  Serial.println(F("Karte entdeckt!"));
  // Dezimal-Wert in String schreiben
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    WertDEZ = WertDEZ + String(mfrc522.uid.uidByte[i], DEC) + " ";
  }
  Serial.println();
  // Kennung dezimal anzeigen
  Serial.println("Wert in dezimal: " + WertDEZ);
  // Leerzeichen am Ende entfernen
  WertDEZ.trim();
  // WertDEZ mit korrektem Wert vergleichen -> Schranke öffnen
  if (WertDEZ.compareTo("80 236 29 59") == 0)
  {
    Serial.println("korrekte Karte -> Schranke \u00f6ffnen");
    Motor.write(90);
    Status = !Status;
  }
  if (WertDEZ.compareTo("80 236 29 59") == 0 && !Status)
  {
    Serial.println("  korrekte Karte/Zutritt erfolgt -> Schranke schlie\u00dfen");
    Motor.write(5);
  }
  // wenn die Karte falsch ist
  else if (WertDEZ.compareTo("80 236 29 59") != 0)
  {
    Motor.write(5);
    Serial.println("falsche Karte -> Schranke geschlossen lassen");
    Status = false;
  }
  delay(1000);
}
