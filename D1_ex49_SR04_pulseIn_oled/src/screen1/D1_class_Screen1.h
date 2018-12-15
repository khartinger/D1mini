//_____D1_class_Screen1.h_____________________170412-180515_____
// The class Screen1 extends the class Screen_64x48 
// with screen methods to write text on the display. Also a
// 5x8 pixel font is included in this file.
//
// Hardware: (1) WeMos D1 mini
//           (2) OLED Shield: SSD1306, 64x48 pixel, I2C, 
//                            default reset pin D3 = GPIO0
//
#ifndef D1_CLASS_SCREEN1_H
#define D1_CLASS_SCREEN1_H
#include "Arduino.h"                   // D3
#include <Wire.h>                      // i2c
#include "D1_class_Screen_64x48.h"     // Basics for Screen1
#ifndef OLED_RESET
 #define OLED_RESET D3                 // OLED_RESET=D3=GPIO0
#endif
#define OLED_I2C    0x3C               // OLED i2c address
#define DOT         String((char)249)  // . 249 or 46 or X=88

class Screen1 : public _Adafruit_SSD1306 {
 //-----properties----------------------------------------------
 protected:
  int dotCounter;
 //-----constructor & co----------------------------------------
 public:
  Screen1();
  Screen1(int oled_resetpin);
 protected: 
  void setup(int pin_num);             // setup properties
 //-----simple screens: one area, 4..6 single size lines--------
 public: 
 void screen6 (int line_, String text_);
 void screen6 (int line_, String text_, char align_);
 void screen6Clear (int line_, String text_);
 void screen6Clear (int line_, String text_, char align_);
 
 void screen6i(int line_, String text_);
 void screen6i(int line_, String text_, char align_);
 void screen6iClear(int line_, String text_);
 void screen6iClear(int line_, String text_, char align_);
 
 void screen5 (int line_, String text_);
 void screen5 (int line_, String text_, char align_);
 void screen5Clear(int line_, String text_);
 void screen5Clear(int line_, String text_, char align_);
 
 void screen5i(int line_, String text_);
 void screen5i(int line_, String text_, char align_);
 void screen5iClear(int line_, String text_);
 void screen5iClear(int line_, String text_, char align_);

 void screen4 (int line_, String text_);
 void screen4 (int line_, String text_, char align_);
 void screen4Clear (int line_, String text_);
 void screen4Clear (int line_, String text_, char align_);
 
 void screen4i(int line_, String text_);
 void screen4i(int line_, String text_, char align_);
 void screen4iClear(int line_, String text_);
 void screen4iClear(int line_, String text_, char align_);

 //-----simple screens: one area, 1..2 double size lines--------
 void screen2 (int line_, String text_);
 void screen2 (int line_, String text_, char align_);
 void screen2Clear(int line_, String text_, char align_);
 
 void screen1 (String text_);
 void screen1 (String text_, char align_);
 void screen1Clear(String text_, char align_);

 //-----screens with more than one area, single size lines------
 void screen221(int line_,String text_, char align_, bool cls_);
 void screen221(int line_,String text_);
 void screen221(int line_,String text_, char align_);
 void screen221Clear(int line_,String text_, char align_);
 
 //----screens with single and double size lines----------------
 void screen112(int line_,String text_, char align_, bool cls_);
 void screen112(int line_,String text_);
 void screen112(int line_,String text_, char align_);
 void screen112Clear(int line_,String text_, char align_);
 
 void screen13(int line_, String text_, char align_, bool cls_);
 void screen13(int line_, String text_);
 void screen13(int line_, String text_, char align_);
 void screen13Clear(int line_, String text_, char align_); 
 
 void screen12(int line_, String text_, char align_, bool cls_); 
 void screen12(int line_, String text_);
 void screen12(int line_, String text_, char align_);
 void screen12Clear(int line_, String text_, char align_);

 //-----screens with 2x button----------------------------------
 void screen4B(int line_, String text_);
 void screen4B(int line_, String text_, char align_);
 void screen4BClear(int line_, String text_);
 void screen4BClear(int line_, String text_, char align_);
 
 void screen4Bi(int line_, String text_);
 void screen4Bi(int line_, String text_, char align_);
 void screen4BiClear(int line_, String text_);
 void screen4BiClear(int line_, String text_, char align_);
 
 //-----special screens-----------------------------------------
 void dotClear(void);                  // clear, draw border
 void dotClear(String line6);          // clear, border, line6
 void dot(void);                       // draw a dot
 void dotLine(String line6);           // write line 6
 
 //-----helper functions----------------------------------------
 public:
  String utf8ToOled(String s);
 
 protected:
 String mytrim(int max_, String txt_, char align);
 void scr6(int line_, String text_, char align_, bool cls_, bool invert_);
 void scr5(int line_, String text_, char align_, bool cls_, bool invert_);
 void scr4(int line_, String text_, char align_, bool cls_, bool invert_);
 void scr4B(int line_, String text_, char align_, bool cls_, bool invert_);
 void screen2 (int line_, String text_, char align_, bool cls_);
 void screen1 (String text_, char align_, bool cls_);
};
#endif
