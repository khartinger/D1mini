# LED control with state machine
Sketch: D1_Ex43_statemachine1.ino, Version 2018-05-04      
[Deutsche Version](./D1_Ex43_statemachine1_LIESMICH.md "Deutsche Version")   
For technical processes it often makes sense to use a state machine.   
For example the blue led on D1 mini should shine like this:   
0.8sec on - 0.4sec off - 0.2sec on - 0.6sec off - ...   
Additional the actual state is printed to Serial (115200Bd):   
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

## Create a state machine   
(1) Define a waiting time in milliseconds, e.g. 100ms   
```
#define DELAY_LOOP             100     // 100ms 
```   

(2) Define states, where something happens, e.g.   
```
#define STATE_LED_ON1            0     // 1. state: led on 
#define STATE_LED_OFF1           8     // 0.8s later: led off
#define STATE_LED_ON2           12     // 0.4s later: led on 
#define STATE_LED_OFF2          14     // 0.2s later: led off
#define STATE_MAX               20     // 0.6s later: loop end
```   

(3) Define a state counter and initialize it
```   
int statecounter=0;                    // actual state number
```   

(4) Implement the states in `loop()` 
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
