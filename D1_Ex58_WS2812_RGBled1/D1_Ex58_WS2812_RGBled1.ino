//_____D1_Ex58_WS2812_RGBled1.ino_____________210507-210507_____
// This program shows the use of ONE RGB-Led WS2812 ("NeoPixel")
// e.g. for color indication of the operating state of a system
// (red = stop, green = active etc.).
// For demonstration the colors red, yellow, green, blue, white
// and orange are displayed for a certain time (e.g. 2 seconds).
// Hardware: 
// (1) WeMos D1 mini (OR ESP32 D1 mini)
// (2) WS1812B RGB shield
//
// Install [Adafruit_NeoPixel_Library] first:
//   https://github.com/adafruit/Adafruit_NeoPixel
// Visual Studio Code: Add line 
//   lib_deps = adafruit/Adafruit NeoPixel@^1.8.0
//   to platformio.ini
// Created by Karl Hartinger, May 07, 2021.
// Changes:
// 2021-05-07 New
// Released into the public domain.
#include <Arduino.h>
#include "Adafruit_NeoPixel.h"
#define  PIN_LED        D2                  // default Pin D2 = 21
#define  C_XX           0x08                // moderate brightness
#define  WAIT_MS        2000                // delay every color

// When we setup the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(1, PIN_LED, NEO_GRB + NEO_KHZ800);

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