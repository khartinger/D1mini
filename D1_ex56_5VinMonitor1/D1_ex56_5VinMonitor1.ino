//_____D1_ex56_5VinMonitor1.ino____________________20210227_____
// This program is used to test the self-made shield 
// `D1_5VinMonitor1` and to measure how long the D1 mini 
// continues to work after the supply voltage is switched off
// (switch-off delay). For this purpose the 5V power supply must
// be connected via the shield and not via the USB connector.
// After power-on pin D5 is set to 1, the blue LED flashes with
// 0.5Hz and the system state is output via the serial interface
// (e.g. `D5=1__LED is on__`). The time control is done with a 
// 10ms counter.
// If the supply voltage is switched off, D5 goes to 0, the LED
// is switched on, the 10ms counter is set to 0 and the counter
// value is sent as a millisecond value via the serial interface
// until the energy stored in the capacitor is used up.
// Hardware:
// 1. WeMos D1 mini (OR ESP32 D1 mini)
// 2. 5V power supply and
//    selfconstruction shield "D1_230Vmonioff1" or
//    prototype shield with voltage divider and backup capacitor
//
// Created by Karl Hartinger, February 27, 2021.
// Changes: 
// 2021-02-27 First release
// Released into the public domain.

#include <Arduino.h>
#define D1MINI          1                   // ESP8266 D1mini+pro
//#define ESP32D1         2                 // ESP32 D1mini
#define  DEBUG56        false //true

//_______sensors, actors, global variables______________________
#if defined(ESP32) || defined(ESP32D1)
 #define PIN_LED         2                  // D4=IO2
 #define LED_ON          1                  // LED on
 #define LED_OFF         0                  // LED off
 #define PIN_DIN_5V     18                  // D5 -> 18
#else
 #define PIN_LED         2                  // D4=IO2
 #define LED_ON          0                  // LED on
 #define LED_OFF         1                  // LED off
 #define PIN_DIN_5V     D5                  // D5 -> 18
#endif
int  led_=LED_ON;                           // start: set...
int  counter_10ms=0;                        // 10ms counter
uint32_t millisLast;                        // last start
uint32_t millisDelay=10;                    // wait 10ms
bool din5Vfirst0=true;                      // 1st time 0

//_______SETUP__________________________________________________
void setup() {
 //------Serial-------------------------------------------------
 Serial.begin(115200); Serial.println("\nsetup(): --Start--");
 //------set pin mode-------------------------------------------
 pinMode(PIN_LED, OUTPUT);                  // blue led...
 digitalWrite(PIN_LED,led_);                // ...led on
 pinMode(PIN_DIN_5V, INPUT);                // 5V sensor
 millisLast=millis();                       // start time
 //------finish setup-------------------------------------------
 Serial.println("setup(): --Finished--\n"); // setup OK
 Serial.println("__");                      // for D1_oop89...
}

//_______LOOP___________________________________________________
void loop() {
 int din5V = digitalRead(PIN_DIN_5V);
 if(din5V==1)
 {//-----power on: switch and show led status-------------------
  din5Vfirst0=true;                         // din5V is 1
  if(counter_10ms % 100==0) {               // switch LED state
   led_=1-led_;                             // invert led value
   Serial.print("D5=1__LED is ");           // send led value...
   if(led_==LED_ON) Serial.println("on__"); // ... via ...
   else Serial.println("off__");            // ... Serial
   digitalWrite(PIN_LED,led_);              // and show LED
  }
 }
 else
 {//-----power off: show milli seconds--------------------------
  if(din5Vfirst0) {
   digitalWrite(PIN_LED,LED_ON);            // led on
   Serial.println("D5=0__LED is on!");      // send led value
   counter_10ms=0;                          // restart counter
   din5Vfirst0=false;                       // done
  }
  Serial.print(counter_10ms);               // send...
  Serial.println("0ms");                    // ...milliseconds
 }
 //------update 10ms counter------------------------------------
 counter_10ms++;                            // increment counter
 if(counter_10ms>6000) counter_10ms=0;      // every minute
 while((millis()-millisLast) < millisDelay) {delay(1); yield();}
 millisLast=millis();
}
