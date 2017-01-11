//_____D1_Ex19_oled_myfont1.ino____________________20170111_____
// Display character 32..255 on OLED shield
//   5 pages, 5 (6) lines with 10 characters
// Hardware: WeMos D1 Mini
//           OLED Shield: SSD1306, 64x48 pixel, I2C
//                        SCL GPIO5, SDA GPIO4, OLED_RESET GPIO0
// Uses Adafruit libs Adafruit_SSD1306-esp8266-64x48.zip and
//                    Adafruit-GFX-Library-1.1.5.zip
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include "fonts/font2_5x8.h"

#define OLED_RESET 0              // OLED_RESET=D3=GPIO0
Adafruit_SSD1306 display(OLED_RESET);

void setup() {
 display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // I2C addr 0x3C
 display.setTextColor(WHITE);
 display.setFont(&font2_5x8);
 //display.setFont(NULL);
 display.setTextSize(1);
}

void loop() {
 char c;
 int i, j, jmin, jmax; 
 //-----show all characters 32...255 on 5 pages-----------------
 for(i=0; i<5; i++)
 {
  jmin=32+i*50;
  jmax=jmin+49;
  if(jmax>255) jmax=255;
  String s=String(jmin)+"-"+String(jmax);
  display.clearDisplay();          // Clear the display-buffer
  display.setCursor(0,0);
  display.println(s);
  //-----print characters---------------------------------------
  for(j=jmin; j<=jmax; j++)
  {
   c=(char)j;
   display.print(c);
  }
  display.display();               // show display-buffer
  //-----wait...------------------------------------------------
  delay(5000);
 }
}
