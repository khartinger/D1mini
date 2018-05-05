# LED control with state machine 2
Sketch: D1_Ex44_statemachine2.ino, Version 2018-05-05    
[Deutsche Version](./D1_Ex44_statemachine2_LIESMICH.md "Deutsche Version")     

If you program state machines with D1 mini, you also can implement special conditions like this:

### Consider processing time of states
If the processing time of states may be longer, you should shorten the delay time. Therefore you define two variables outside the `loop()`:
``` 
long loop_delay=DELAY_LOOP;            // loop delay [ms]
long loop_millis=0;                    // loop duration [ms]
``` 
The variable `loop_millis` saves the start time of the loop. If you subtract that time from the end time you get the duration of the loop pass.   
Reduce `loop_delay` by this value:   
``` 
 loop_millis=millis()-loop_millis;          // loop duration
 loop_delay=loop_delay-loop_millis;         // rest delay
 if(loop_delay<0) loop_delay=0;             // time >= 0
``` 

Change the `delay()` command in `loop()` this way:
```  
 delay(loop_delay);                         // wait
 loop_delay=DELAY_LOOP;                     // set next delay
}
```  

### System not ready in a state
If the system is not ready to do something in a state, you can try to do this action in the next state.   
Define __additionally__ to the constant a  __variable__:   
```  
 int state_1=STATE_1;
```  

Change the state like this way:   
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

## Hardware
* WeMos D1 Mini

## Demo program
This example program shows 
* a state, that lasts a little longer (LED on with "delay"),
* a state that "postpones a state" (LED off is only allowed after a waiting time of min. 0.6 sec),
* measuring the loop pass (state duration), print state number and action to Serial.

The blue LED should blink by default like this:   
0.8s on - 0.4s off - 0.2s on - 0.6s off - ...    
(= a long and a short shining of the LED)   
_Special condition:_    
After led is on it must shine for 0.6 seconds.   

To see the time consumation of Serial printing, use a Baudrate of e.g. 9600 Baud and execute the command `Serial.flush();` before the end of time/duration measuring. (This command waits until the last character is sent.)   

### Serial output (@9600Bd)
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

## Create a state machine   
(1) Define a waiting time in milliseconds, e.g. 200ms   
```
#define DELAY_LOOP             200     // 200ms 
```   

(2) Define states, where something happens, e.g.   
```
#define STATE_LED_ON1            0     // 1. state: led on 
#define STATE_LED_OFF1           4     // 0.8s later: led off
#define STATE_LED_ON2            6     // 0.4s later: led on 
#define STATE_LED_OFF2           7     // 0.2s later: led off
#define STATE_MAX               10     // 0.6s later: loop end
```   

(3) Define a state counter and state variables for "postpones  states" and initialize them:
```   
int statecounter=0;
int state_led_off1=STATE_LED_OFF1;
int state_led_off2=STATE_LED_OFF2;
```   

(4) Define variable for special conditions and loop pass duration:
```   
long millisLastOn=0;                   // time of last led on
long loop_delay=DELAY_LOOP;            // loop delay [ms]
long loop_millis=0;                    // loop duration [ms]
```   

(5) Implement states in `loop()`:   
See above and/or example program.
