//_____D1_Ex23_int_io_mytimer1.ino_________________20170122_____
// Rising edge on D3 (=GPIO0, Button) turns blue LED (D4=GPIO2)
// on, falling edge on D3 turns blue LED off.
// If Button is pressed more than 2sec, LED is turned off
// 
// Hardware: WeMos D1 mini
//           1-Button Shield
extern "C" {
#include "user_interface.h"
}
const int pinButton=D3;
const int pinLED=D4;
os_timer_t myTimer;

//_____io interrupt service routine_____________________________
ICACHE_RAM_ATTR void io_ISR(void)
{
 if(digitalRead(pinButton)==0)
 { //-----falling edge = Button pressed-------------------------
  digitalWrite(pinLED, 0);                       //LED on
  //.....start timer............................................
  os_timer_disarm(&myTimer);                     //stopp timer
  os_timer_setfn(&myTimer, myTimer_ISR, NULL);   //NULL:no param
  os_timer_arm(&myTimer, 2000, false);           //2000ms, 1x
 }
 else
 { //-----rising edge = Button released-------------------------
  digitalWrite(pinLED, 1);                       //LED off
  os_timer_disarm(&myTimer);                     //stopp timer
 }
}

//_____mytimer1 interrupt service routine_______________________
ICACHE_RAM_ATTR void myTimer_ISR(void *pArg) {
 digitalWrite(pinLED, 1);                       //LED off
}

void setup() {
 //-----Hardware------------------------------------------------
 pinMode(pinLED, OUTPUT);
 pinMode(pinButton, INPUT);
 digitalWrite(pinLED, 1);
 //-----io interrupt--------------------------------------------
 attachInterrupt(digitalPinToInterrupt(pinButton), io_ISR, CHANGE); // FALLING,...
}

void loop() {
 yield();                                        // or delay(0); 
}
