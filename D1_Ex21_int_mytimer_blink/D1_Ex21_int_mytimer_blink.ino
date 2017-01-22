//_____D1_Ex21_int_mytimer_blink.ino_______________20170120_____
// ESP8266 timer interrupt example:  blue LED blinks with 1 Hz 
// Hardware: D1mini
// See also: http://www.switchdoc.com/2015/10/iot-esp8266-timer-tutorial-arduino-ide/
extern "C" {
#include "user_interface.h"
}

const int pinLED=D4;
os_timer_t myTimer;

//_____mytimer interrupt service routine________________________
void mytimer_ISR(void *pArg) {
 digitalWrite(pinLED, digitalRead(pinLED)^1);    // invert LED
}

void setup() {
 pinMode(pinLED, OUTPUT);
 //-----set timer function and delay time-----------------------
 os_timer_setfn(&myTimer, mytimer_ISR, NULL);    //NULL:no param
 os_timer_arm(&myTimer, 500, true);              //500ms, repeat
}

void loop() {
 yield();                                        // or delay(0); 
}
