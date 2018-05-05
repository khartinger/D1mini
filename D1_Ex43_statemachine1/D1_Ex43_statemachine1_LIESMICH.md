# LED-Steuerung mittels Zustandsmaschine
Sketch: D1_Ex43_statemachine1.ino, Version 2018-05-04      
[English Version](./D1_Ex43_statemachine1_README.md "English Version")   

F&uuml;r Steuerungsaufgaben ist es oft sinnvoll, den Ablauf auf dem D1mini als Statemachine (&auml;hnlich einer SPS) zu programmieren.   
Als Beispiel soll die blaue LED in folgendem Rhythmus leuchten:   
0,8sec ein - 0,4sec aus - 0,2sec ein - 0,6sec aus - ...   
Zus&auml;tzlich soll der aktuelle State &uuml;ber die serielle Schnittstelle angezeigt werden (115200Bd):   
```
-----------------
State 0: LED on
State 1: 
State 2: 
State 3: 
State 4: 
State 5: 
State 6: 
State 7: 
State 8: LED off
State 9: 
State 10: 
State 11: 
State 12: LED on
State 13: 
State 14: LED off
State 15: 
State 16: 
State 17: 
State 18: 
State 19: 
-----------------
State 0: LED on
State 1: 
```   

## Hardware
* WeMos D1 Mini

## Erstellen der Statemachine   
(1) Definition einer loop-Wartezeit in Millisekunden, zB 100ms   
```
#define DELAY_LOOP             100     // 100ms 
```   

(2) Definition der States (Zust&auml;nde), in denen etwas passieren soll, zB   
```
#define STATE_LED_ON1            0     // 1. state: led on 
#define STATE_LED_OFF1           8     // 0.8s later: led off
#define STATE_LED_ON2           12     // 0.4s later: led on 
#define STATE_LED_OFF2          14     // 0.2s later: led off
#define STATE_MAX               20     // 0.6s later: loop end
```   

(3) Definition eines Statusz&auml;hlers und Initialisierung
```   
int statecounter=0;                    // actual state number
```   

(4) Implementierung der einzelnen States in `loop()` 
```
void loop()
{
 //-----states--------------------------------------------------
 if(statecounter==STATE_LED_ON1)
 {
  //...ToDo... led on
 }
 if(statecounter==STATE_LED_OFF1)
 {
  //...ToDo... led off
 }
 //... Do all other cases = states ...
 //-----prepare for next state----------------------------------
 if((++statecounter)>=STATE_MAX) statecounter=0;
 delay(DELAY_LOOP);
}
```  
