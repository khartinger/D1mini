# D1 mini: Infos &uuml;ber eine microSD-Karte im Micro SD Shield
Sketch: D1_Ex40_SD_cardinfo, Version 2017-11-05   
[English Version](./README.md "English Version")

Dieses Beispiel basiert auf Code von Limor Fried und Tom Igoe auf https://github.com/esp8266/Arduino/blob/master/libraries/SD/examples/CardInfo/CardInfo.ino

Nach dem Einschalten wird &uuml;ber die serielle Schnittstelle angezeigt,
* ob sich eine microSD-Karte in der Halterung befindet,
* von welchem Typ die Karte ist (SD1, SD2 oder SDHC),
* ob die Karte FAT16 oder FAT32 formatiert ist,
* wie gro&szlig; die Anzahl Bl&ouml;cke pro Cluster, Anzahl Cluster und die Speichergr&ouml;&szlig;e ist,
* welche Dateien sich im Root-Verzeichnis befinden.

## Hardware
* WeMos D1 mini
* Micro SD Shield

![Bild: D1mini mit micro SD Shield](./images/D1_microSD.png "D1mini mit Micro SD Shield")   

### Ausgabe auf der seriellen Schnittstelle
```
PART 1: Initializing SD card...
Wiring is correct and a card is present.
Card type: SDHC

PART 2: volume info
Volume type: FAT32
Block size: 512 byte (fix)
Number of blocks per cluster: 16
Number of clusters: 1942528
Volume size (KBytes): 15540224
Volume size (MBytes): 15176
Volume size (GBytes): 14

PART 3: Files found on the micro SD card.
--filename.ext |---date---|--time--|size in bytes
  SYSTEM~1/     2017-11-04 19:55:08
  WPSETT~1.DAT  2017-11-04 19:55:08 12
  INDEXE~1      2017-11-04 19:55:12 76
```

---

## FAT32-Formatieren von microSD-Karten mit Windows
Beachte: Die Anleitung gilt f&uuml;r microSD-Kartengr&ouml;&szlig;en von 512MB bis 32GB!   
Kleinere microSD-Karten : FAT16 formatieren   
Gr&ouml;&szlig;ere microSD-Karten  : zB folgende Tools verwenden:   
`https://www.heise.de/download/product/h2format-40825` (f&uuml;r unformatierte Karten) oder   
`http://www.heise.de/download/fat32formatter.html`   
&nbsp;   

__F&uuml;r Kartengr&ouml;&szlig;en von 512MB bis 32GB__   
1. Zu formatierende MicroSD-Karte in einen Kartenleser einlegen.
2. Windows-Eingabeaufforderung __als Administrator__ &ouml;ffnen.   
(`C:\Windows\System32\cmd.exe` mit rechter Maustaste "Als Administrator &ouml;ffnen)
3. Partitionsmanager starten durch Eintippen von `diskpart`   
4. Liste der Datentr&auml;ger anzeigen durch Eintippen von `list disk`   
__Wichtig__: Die Nummer des Datentr&auml;gers merken, der formatiert werden soll (zB 5)   
5. Datentr&auml;ger f&uuml;r die weitere Bearbeitung ausw&auml;hlen durch Eintippen von `select disk 5` (bzw. die richtige Datentr&auml;gernummer eingeben).   
Ergebnis: `Datentraeger 5 ist jetzt der gewaehlte Datentraeger.`
6. Alle Daten auf dem Datentr&auml;ger l&ouml;schen durch Eintippen von `clean`   
Ergebnis: `Der Datentraeger wurde bereinigt.`
7. Erstellen der Partition durch Eintippen von `create partition primary`   
Ergebnis: `Die angegebene Partition wurde erfolgreich erstellt.`   
8. Formatieren der microSD-Karte durch Eintippen von `format fs=fat32 quick`   
Ergebnis:    
Sollte das Ergebnis hingegen folgende Meldung sein: `Fehler beim Dienst fuer virtuelle Datentraeger: Die Volumegroesse ist zu gross.`, dann das oben angegebene  Tool verwenden!
9. Optional: Windows-Laufwerksbuchstaben zuordnen durch Eintippen von `assign letter=X`, wobei X der gew&uuml;nschte Buchstabe ist.   
10. Programm beenden durch Eintippen von `exit`.   

*Quelle: http://www.giga.de/downloads/windows-10/tipps/loesung-windows-konnte-die-formatierung-nicht-abschliessen-fehler-beheben/*
