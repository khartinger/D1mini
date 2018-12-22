# D1 mini: Software Serial - Demo 1
Version 2018-11-01, Datei: `D1_Ex50_softwareserial_bytes_io.ino`   
[English version](./README.md "English version")   

Das Programm liest Zeichen von einer durch Software realisierten seriellen Schnittstelle ein (9600 Bd, D6=Rx, D5=Tx), wandelt sie in Gro&szlig;buchstaben um und sendet sie zur&uuml;ck (Echo).   
Die enpfangenen Zeichen werden zus&auml;tzlich zur Kontrolle  auf die hardware-serielle Schnittstelle ausgegeben.   
Zur Kontrolle blinkt die blaue LED im 2Hz-Takt, damit man sieht, dass das Programm l&auml;uft.


## Hardware
1. WeMos D1 mini   
2. PC mit RS232-3V3-Konverter und Terminal-Software   
   Verbindung: D1mini D5 (=Tx) mit RxD, D6 (=Rx) mit TxD, GND mit GND und 3V3 mit 3V3.   

__Wichtig__: Die Pins des D1 mini d&uuml;rfen nur an 3,3V angeschlossen werden!   

## Software
Zur Ansteuerung der software-seriellen Schnittstelle wird die Bibliothek `#include <SoftwareSerial.h>` verwendet.

