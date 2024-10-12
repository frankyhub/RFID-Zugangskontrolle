<a name="oben"></a>

<div align="center">

|[:skull:ISSUE](https://github.com/frankyhub/RFID-Zugangskontrolle/issues?q=is%3Aissue)|[:speech_balloon: Forum /Discussion](https://github.com/frankyhub/RFID-Zugangskontrolle/discussions)|[:grey_question:WiKi](https://github.com/frankyhub/RFID-Zugangskontrolle/wiki)||
|--|--|--|--|
| | | | |
|![Static Badge](https://img.shields.io/badge/RepoNr.:-%2050-blue)|<a href="https://github.com/frankyhub/RFID-Zugangskontrolle/issues">![GitHub issues](https://img.shields.io/github/issues/frankyhub/RFID-Zugangskontrolle)![GitHub closed issues](https://img.shields.io/github/issues-closed/frankyhub/RFID-Zugangskontrolle)|<a href="https://github.com/frankyhub/RFID-Zugangskontrolle/discussions">![GitHub Discussions](https://img.shields.io/github/discussions/frankyhub/RFID-Zugangskontrolle)|<a href="https://github.com/frankyhub/RFID-Zugangskontrolle/releases">![GitHub release (with filter)](https://img.shields.io/github/v/release/frankyhub/RFID-Zugangskontrolle)|
|![GitHub Created At](https://img.shields.io/github/created-at/frankyhub/RFID-Zugangskontrolle)| <a href="https://github.com/frankyhub/RFID-Zugangskontrolle/pulse" alt="Activity"><img src="https://img.shields.io/github/commit-activity/m/badges/shields" />| <a href="https://github.com/frankyhub/RFID-Zugangskontrolle/graphs/traffic"><img alt="ViewCount" src="https://views.whatilearened.today/views/github/frankyhub/github-clone-count-badge.svg">  |<a href="https://github.com/frankyhub?tab=stars"> ![GitHub User's stars](https://img.shields.io/github/stars/frankyhub)|
</div>



# RFID-Zugangskontrolle
Türschloss, LED-Anzeige, Relais-Anschluss oder Servo-Motor

![Bild](pic/rfid3.jpg)

## Story

Mit diesem Projekt wird ein RFID-Kartenleser (RFID=radio frequency identification) für eine Zugangskontrolle eingesetzt. Zunächst muss der RFID-Transponder oder die RFID-Karte ausgelesen werden. Der ausgelesene "Code" wird im Hauptprogramm für den Zugang verwendet und z.B. ein Türschloss geöffnet.
Die Grüne LED zeigt blinkend die Verwendung des korrekten Transponder an, die rote LED zeigt blinkend einen ungültigen Transponder an. Ein Ausgang ist für einen Relais-Anschluss für ein Türschloss vorgesehen und ein Ausgang optional für einen Servo-Motor.

## Hardware

Die Stückliste für die RFID-Zugangskontrolle:

+ 1 x Arduino NANO
+ 1 x RFID-RC522 Modul
+ 1 x Transponder mit Schlüsselring
+ 1 x Transponder im Kartenformat
+ 1 x Relais für den Türöffner (optional)
+ 1 x rote LED mit 100R Vorwiderstand
+ 1 x grüne LED mit 100R Vorwiderstand
+ 1 x Buzzer (optional)
+ 1 x Relais für den Türöffner (optional)
+ 1 x Servo-Motor (optional)
+ Kleinmaterial, Schaltdraht

## Verdrahtung

![Bild](pic/rfid1.png)

+ NANO D2 -> grüne LED
+ NANO D3 -> rote LED
+ NANO D4 -> Buzzer
+ NANO D5 -> Relais
+ NANO D7 -> ServoMotor

## Software
Die Software wird mit der Arduino IDE in den NANO geladen.

+ Mit dem Programm "01-RFID_Auslesen_NANO.ino" wird die RFID-ID aus dem Transponder oder Karte ausgelesen.
+ Das Programm "04_RFID_LED_ansteuern_2_Karten_Servo_LAB_NANO.ino" ist das Hauptprogramm für die Zugangskontrolle.

RFID-Code mit dem Seriellen Monitor auslesen

![Bild](pic/rfid4.png)

![Bild](pic/rfid4dpng.png)


RFID-Zugangsinformationen mit dem Seriellen Monitor auslesen

![Bild](pic/rfid4c.png)




## Aufbau der RFID-Zugangskontrolle

![Bild](pic/rfid2.jpg)

## RFID-Zugangskontrolle mit Servo-Motor Verschlusseinheit

![Bild](pic/rfid3.jpg)


## PIN-OUT RFID-Shield

![Bild](pic/rfid5.jpg)



---

<div style="position:absolute; left:2cm; ">   
<ol class="breadcrumb" style="border-top: 2px solid black;border-bottom:2px solid black; height: 45px; width: 900px;"> <p align="center"><a href="#oben">nach oben</a></p></ol>
</div>  

---












