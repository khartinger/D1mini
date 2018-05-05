# LED-Steuerung mittels Zustandsmaschine 2
Sketch: D1_Ex44_statemachine2.ino, Version 2018-05-05      
[English Version](./D1_Ex44_statemachine2_README.md "English Version")   

Programmiert man Steuerungsaufgaben mit dem D1mini als Statemachine, so kann man auch Sonderf&auml;lle ber&uuml;cksichtigen. Zum Beispiel:

### Ber&uuml;cksichtigung der Bearbeitungszeit in States
Ist zu erwarten, dass die Bearbeitung in einem oder mehreren Zust&auml;nden (state) etwas l&auml;nger dauert, so sollte man die loop-Wartezeit entsprechend verk&uuml;rzen. Dazu kann man zB au&szlig;erhalb des `loop()` zwei Variable definieren:   
``` 
long loop_delay=DELAY_LOOP;            // loop delay [ms]
long loop_millis=0;                    // loop duration [ms]
``` 
Die Variable `loop_millis` merkt sich dabei die Startzeit des aktuellen Schleifendurchlaufs (loops) und durch Subtraktion von der Ende-Zeit erh&auml;lt man die Dauer des Schleifendurchlaufs.   
Die Variable `loop_delay` wird entsprechend der Dauer verk&uuml;rzt:   
``` 
 loop_millis=millis()-loop_millis;          // loop duration
 loop_delay=loop_delay-loop_millis;         // rest delay
 if(loop_delay<0) loop_delay=0;             // time >= 0
``` 

Weiters muss die Wartezeit im `loop()` folgenderma&szlig;en ge&auml;ndert werden:
```  
 delay(loop_delay);                         // wait
 loop_delay=DELAY_LOOP;                     // set next delay
}
```  

### System nicht bereit in einem State
Soll in einem State eine Aktion ausgef&uuml;hrt werden, jedoch ist das dazugeh&ouml;rige System (noch) nicht bereit, so kann man versuchen, die Aktion im n&auml;chsten State auszuf&uuml;hren. Dazu muss man f&uuml;r diesen State __zus&auml;tzlich__ zur Konstanten noch eine __Variable__ definieren:   
```  
 int state_1=STATE_1;
```  

Die Bearbeitung dieses States muss dann folgenderma&szlig;en erfolgen:   
```  
 if(statecounter==state_1)             // number of state
 {
  if(isSystemReady())                  // special condition
  {
   state_1=STATE_1;                    // for next time
   // Do what needs to be done .....
  }
  else 
  {
   if((++state_1)>=STATE_MAX) state_1=0; // set next state
  }
 }
```
Ist das System nicht bereit, wird der State `state_1` um 1 erh&ouml;ht. Sollte der Wert zu gro&szlig; werden, wird er auf 0 gesetzt.   
Ist das System jedoch bereit, wird der State-Wert zur Sicherheit wieder auf den Vorgabewert gesetzt und die Aktion ausgef&uuml;hrt.   

## Hardware
* WeMos D1 Mini

## Beispielprogramm
Das Beispielprogramm demonstriert 
* einen State, der etwas l&auml;nger dauert (LED on mit "Wartezeit"),
* das "Hinausschieben eines States" (LED off darf erst nach mindestens 0,6 sec geschehen)
* das Messen der State-Dauer und die Anzeige der durchgef&uuml;hrten Aktion &uuml;ber die serielle Schnittstelle.

Die blaue LED soll "planm&auml;&szlig;ig" in folgendem Rhythmus leuchten:   
0,8s ein - 0,4s aus - 0,2s ein - 0,6s aus - ...    
(= ein l&auml;ngeres und ein kurzes Aufleuchten der LED)   
_Zus&auml;tzliche Forderung:_    
Nach jedem Einschalten der LED muss diese mindestens 0,6s leuchten.   

Damit man auch den Zeitbedarf der seriellen &Uuml;bertragung sieht, kann man die Baudrate auf zB 9600 Baud einstellen und VOR Ende der Zeitmessung den Befehl `Serial.flush();` einbauen. Dieser Befehl wartet, bis das Senden der Zeichen abgeschlossen ist.   

### Ausgabe auf Serielle Schnittstelle (@9600Bd)
```   
------------------------
State 0: LED on (190+10 ms)
State 1:  (12+188 ms)
State 2:  (8+192 ms)
State 3:  (8+192 ms)
State 4: LED off (16+184 ms)
State 5:  (9+191 ms)
State 6: LED on (190+10 ms)
State 7: ***NOT*** LED off (30+170 ms)
State 8: ***NOT*** LED off (26+174 ms)
State 9: LED off (15+185 ms)
------------------------
State 0: LED on (191+9 ms)
State 1:  (13+187 ms)
State 2:  (8+192 ms)
```   

&nbsp;   

## Erstellen der Statemachine   
(1) Definition einer loop-Wartezeit in Millisekunden, zB 200ms   
```
#define DELAY_LOOP             200     // 200ms 
```   

(2) Definition der States (Zust&auml;nde), in denen etwas passieren soll, zB   
```
#define STATE_LED_ON1            0     // 1. state: led on 
#define STATE_LED_OFF1           4     // 0.8s later: led off
#define STATE_LED_ON2            6     // 0.4s later: led on 
#define STATE_LED_OFF2           7     // 0.2s later: led off
#define STATE_MAX               10     // 0.6s later: loop end
```   

(3) Definition von Statusz&auml;hler und Status-Variable f&uuml;r "hinausschiebbare" States incl. Initialisierung
```   
int statecounter=0;
int state_led_off1=STATE_LED_OFF1;
int state_led_off2=STATE_LED_OFF2;
```   

(4) Definition von Variablen f&uuml;r die Spezialbedingung und die loop-Zeitmessung
```   
long millisLastOn=0;                   // time of last led on
long loop_delay=DELAY_LOOP;            // loop delay [ms]
long loop_millis=0;                    // loop duration [ms]
```   

(5) Implementierung der einzelnen States in `loop()`   
Siehe oben bzw. Beispielprogramm.
