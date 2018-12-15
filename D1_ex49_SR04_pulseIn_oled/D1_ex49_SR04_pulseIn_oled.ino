//_____D1_Ex49_SR04_pulseIn_oled.ino__________180330-181101_____
// Measure distance with a ultrasonic sensor HC-SR04 (HY-SRF05)
// every second and print result to oled 0.66". 
// Pulse width is measured using pulseIn (max. 30ms blocking)
// Hardware: 1. WeMos D1 mini
//           2. Ultrasonic sensor HY-SRF05
//           3. OLED Shield: SSD1306, 64x48 pixel, I2C (0x3C)
// Connect ultrasonic sensor:
// Do not connect echo pin (5V) directly to D1 mini (3V3)!
// On D1 mini not every pin is suitable for connecting to
// SR-04 echo pin because of 10k Pull-up Resistors (D3, D4).
//
// VCC------------------5V
// Trig-----------------D3
// Echo---|4k7|---*-----D5
//                |
//               10k
//                |
// GND------------*-----GND
//
// Macro US2CM: convert measured PWM time [us] to distance [cm].
// Formula for approximate speed of sound in dry (0% humidity)
// air see https://en.wikipedia.org/wiki/Speed_of_sound
// Created by Karl Hartinger, November 01, 2018.
// Last modified: -
// Released into the public domain.
//
#include "src/screen1/D1_class_Screen1.h"
#define US2CM(us,T)     ((331.3+0.606*T)*us/20000)
#define PIN_TRIG        D3             // D4
#define PIN_ECHO        D5             //
int T=20.0;                            // Temperature in deg C
Screen1 display_;                      // display object

void setup() {
 Serial.begin(115200);Serial.println();// init serial comm
 pinMode(PIN_TRIG, OUTPUT);            // 
 pinMode(PIN_ECHO, INPUT);             //
 digitalWrite(PIN_TRIG, LOW);          // prepare for plus pulse
 Serial.println("\nHY-SRF05 started"); // next line, info text
 //-----init oled-----------------------------------------------
 display_.screen112Clear(1,"ABSTAND",'c');
 display_.screen112(4,"1.11.18 KH",'c');
}
 
void loop()
{
 long durationUs, distanceCm;          // 
 float distanceCmf;                    //distance as float value
 //-----do measuring--------------------------------------------
 Serial.print("Start measuring... -> Duration in us = "); // info text
 digitalWrite(PIN_TRIG, HIGH);         // start pulse
 delayMicroseconds(11);                // wait 11us (min.: 10us)
 digitalWrite(PIN_TRIG, LOW);          // end of pulse
 durationUs = pulseIn(PIN_ECHO, HIGH, 30000); // measure time
 Serial.println(durationUs);
 distanceCm = durationUs / 29.1 / 2 ;  // calculate distance as
 distanceCmf = US2CM(durationUs,T);    // long and float
 //-----print result--------------------------------------------
 if (distanceCm <= 0){
  Serial.println("Out of range");
  display_.screen112(2,"OUT",'c');
  display_.screen112(3,"of range",'c');
  
 }
 else {
  Serial.print(distanceCmf,0);         // no decimal places
  Serial.print("cm (float) = ");       // print unit
  Serial.print(distanceCm);            // long value
  Serial.println("cm (long)");         // print unit
  display_.screen112(2,String(distanceCm),'c');
  display_.screen112(3,"cm",'c');
 }
 delay(1000);                          // wait 1 second
}
