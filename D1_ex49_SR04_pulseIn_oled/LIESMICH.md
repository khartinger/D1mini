# Di mini: Abstandmessung mit Ultraschallsensor HC-SR04
Version 2018-11-16, Datei: `D1_Ex49_SR04_pulseIn_oled.ino`   
[English version](./README.md "English version")   

Der mit dem Ultraschallsensor HC-SR04 gemessene Abstand wird auf dem 0.66" OLED in cm angezeigt.   
![D1mini mit HC04 Sensor](./images/D1_SR04_1.png "D1 mini mit HC04 Sensor")   
_Bild 1: D1mini mit Adapter und Ultraschallsensor HC-SR04_ 

## Hardware
1.  WeMos D1 mini   
2.  Eigenbau ProtoBoard SR04-Adapter mit Ultraschallsensor HC-SR04   
3.  OLED Shield 0.66"   

![D1 SR04-Adapter Schaltung](./images/D1_HC-SR04_Adapter_circuit1.png "Schaltung D1mini mit HC04 Sensor")   
_Bild 2: Schaltung des D1mini Adapters f&uuml;r Ultraschallsensor HC-SR04_ 

![D1 Bauteilseite HC-SR04-Adapter](./images/D1_SR04_comp1.png "Bauteilseite HC-SR04-Adapter")   
_Bild 3: Bauteilseite des HC-SR04-Adapters_ 

![D1 L&ouml;tseite HC-SR04-Adapter](./images/D1_SR04_solder1.png "L&ouml;tseite HC-SR04-Adapter")   
_Bild 4: L&ouml;tseite des HC-SR04-Adapters_ 

## Software
Zur Ansteuerung des OLED wird die Klasse `Screen1` verwendet.   
(Siehe Verzeichnis `src`)   

