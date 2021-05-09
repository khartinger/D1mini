//_____D1_Ex59_WS2812_Trafficlight.ino________210509-210509_____
// This program shows the use of 3 RGB-Leds WS2812 ("NeoPixel")
// as a traffic light.
// Hardware: 
// (1) WeMos D1 mini (OR ESP32 D1 mini)
// (2) 3x WS1812B RGB leds
//
// Install [Adafruit_NeoPixel_Library] first:
//   https://github.com/adafruit/Adafruit_NeoPixel
// Visual Studio Code: Add line 
//   lib_deps = adafruit/Adafruit NeoPixel@^1.8.0
//   to platformio.ini
// Created by Karl Hartinger, May 09, 2021.
// Changes:
// 2021-05-09 New
// Released into the public domain.
#include <Arduino.h>
#include "Adafruit_NeoPixel.h"
#define  PIN_LED        D2                  // default Pin D2 = 21
#define  C_XX           0x08                // moderate brightness
#define  C_XY           0x05                // moderate brightness
#define  WAIT_MS_1      600                 // delay green blink
#define  WAIT_MS_2      1500                // delay red+orange
#define  WAIT_MS_3      3000                // delay red, green
// When we setup the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(3, PIN_LED, NEO_GRB + NEO_KHZ800);

//_______set pixel color and send it to RGB LED_________________
void RGBled(int red_, int green_, int blue_)
{
 if(red_  >0xFF) red_  =0xFF;
 if(green_>0xFF) green_=0xFF;
 if(blue_ >0xFF) blue_ =0xFF;
 pixels.setPixelColor(0, pixels.Color(red_,green_,blue_));
 pixels.show();                             // send to hardware
}

//_______SETUP__________________________________________________
void setup() {
  pixels.begin();                           // init NeoPixel library
}

//_______LOOP___________________________________________________
void loop() {
 //------red----------------------------------------------------
 pixels.setPixelColor(0, pixels.Color(0x00,0x00,0x00)); //green
 pixels.setPixelColor(1, pixels.Color(0x00,0x00,0x00)); //orange
 pixels.setPixelColor(2, pixels.Color(C_XX,0x00,0x00)); //red
 pixels.show();                             // send to hardware
 delay(WAIT_MS_3);                          // wait
 //------red + orange-------------------------------------------
 pixels.setPixelColor(1, pixels.Color(C_XX,C_XY,0x00)); //orange
 pixels.show();                             // send to hardware
 delay(WAIT_MS_2);                          // wait
 //------green--------------------------------------------------
 pixels.setPixelColor(0, pixels.Color(0x00,C_XX,0x00)); //green
 pixels.setPixelColor(1, pixels.Color(0x00,0x00,0x00)); //orange
 pixels.setPixelColor(2, pixels.Color(0x00,0x00,0x00)); //red
 pixels.show();                             // send to hardware
 delay(WAIT_MS_3);                          // wait
 //------green blinking-----------------------------------------
 for(int i=4; i>0; i--) {
  pixels.setPixelColor(0,pixels.Color(0x00,0x00,0x00)); //green
  pixels.show();                            // send to hardware
  delay(WAIT_MS_1);                         // wait
  pixels.setPixelColor(0,pixels.Color(0x00,C_XX,0x00)); //green
  pixels.show();                            // send to hardware
  delay(WAIT_MS_1);                         // wait
 }
 //------orange-------------------------------------------------
 pixels.setPixelColor(0, pixels.Color(0x00,0x00,0x00)); //green
 pixels.setPixelColor(1, pixels.Color(C_XX,C_XY,0x00)); //orange
 pixels.show();                             // send to hardware
 delay(WAIT_MS_2);                          // wait
}
/*
  RGBled(C_XX,0x00,0x00);                   // red
  delay(WAIT_MS);
  RGBled(C_XX,C_XX,0x00);                   // yellow
  delay(WAIT_MS);
  RGBled(0x00,C_XX,0x00);                   // green
  delay(WAIT_MS);
  RGBled(0x00,0x00,C_XX);                   // blue
  delay(WAIT_MS);
  RGBled(C_XX,C_XX,C_XX);                   // white
  delay(WAIT_MS);
  RGBled(C_XX,C_XX>>1,0x00);                // orange
  delay(WAIT_MS);
  RGBled(0x00,0x00,0x00);                   // out
  delay(WAIT_MS);
}
*/