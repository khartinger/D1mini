//_____D1_Ex20_text2oled2.ino______________________20170111_____
// Display text with special characters on OLED shield.
// UTF8 characters have to be converted for oled!
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

#define DEBUG 1
#define OHM    "\xE9"
#define ALPHA  "\xDF"
#define OLED_RESET 0              // OLED_RESET=D3=GPIO0
Adafruit_SSD1306 display(OLED_RESET);

//_____convert utf8-String to ssd1306-String____________________
String utf8_to_ssd1306(String s)
{
 String s2="";
 int i, i1,i2;
 int len_=s.length();
 //-----search utf8-string--------------------------------------
 for(i=0; i<len_; i++)
 {
  if(isAscii(s.charAt(i)))
   s2=s2+s.charAt(i);             // char is ASCII-Code -> ok
  else //.....not a ascii code..................................
  {
   //.....16 bit value..........................................
   i1=((int)s.charAt(i))*256+((int)s.charAt(i+1));
   i++;
   Serial.println("Not ASCII: i1="+String(i1,16));
   switch(i1)
   {
    case 0xE282: //.....32 bit value............................
     if((i+2)<=len_)
     {
      i2=((int)s.charAt(i+1))*256+((int)s.charAt(i+2));
      i=i+2;
      switch(i2)
      {
       case 0xAC00: s2=s2+"\x80";      // €
       break;   
       default: s2=s2+"\xFF"; break;   // FF on Error
      }
     } 
     break;
    //.....convert 16 bit values................................
    case 0xC384: s2=s2+"\x8E"; break;  // Ä
    case 0xC396: s2=s2+"\x99"; break;  // Ö
    case 0xC39C: s2=s2+"\x9A"; break;  // Ü
    case 0xC3A4: s2=s2+"\x84"; break;  // ä
    case 0xC3B6: s2=s2+"\x94"; break;  // ö
    case 0xC3BC: s2=s2+"\x81"; break;  // ü
    case 0xC39F: s2=s2+"\xE0"; break;  // ß
    case 0x03B1: s2=s2+"\xDF"; break;  // alpha
    case 0xC2B0: s2=s2+"\xF7"; break;  // °
    default: s2=s2+"\xFF"; break;      // FF on Error
   }
  };
 }
 return s2;
}

void setup() {
 char c;
 int i, di=60;
 if(DEBUG) { Serial.begin(57600); Serial.println(); }
 //-----prepair display-----------------------------------------
 display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // I2C addr 0x3C
 display.setTextColor(WHITE);
 display.setFont(&font2_5x8);
 //display.setFont(NULL);
 display.setTextSize(1);
 display.clearDisplay();
 //-----prepair text strings------------------------------------
 String s1="ÄÖÜ äöü ß";
 String s1new=utf8_to_ssd1306(s1);
 if(DEBUG) Serial.println("s1="+s1+"\ns1new="+s1new); 
 double r1=2.2;
 String s2new="R1="+String(r1)+"k"+OHM;
 String s3="=90°";
 String s3new=utf8_to_ssd1306(s3);
 s3new=ALPHA+s3new;                 // 0cDF=Alpha
 String s4="k=0,20€";
 String s4new=utf8_to_ssd1306(s4);
 //-----write characters to display buffer----------------------
 display.println("Specials:");
 display.println(s1new);
 display.println(s2new);
 display.println(s3new);
 display.println(s4new);
 //-----show display buffer-------------------------------------
 display.display();               // show buffer
}

void loop() {
}
