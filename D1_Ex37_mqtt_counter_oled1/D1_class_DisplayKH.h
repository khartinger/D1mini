//_____D1_class_DisplayKH.h___________________170412-170620_____
// The class DisplayKH extends the class Adafruit_SSD1306,
//  so you can use all commands from this class as well.
// Additionally a 5x8 pixel font is included in this class.
// The Adafruit-files in /libs are copied from the libs
//  * Adafruit_SSD1306-esp8266-64x48.zip and
//  * Adafruit-GFX-Library-1.1.5.zip
// When using the Adafruit libs, delete the directory /libs !
//
// Hardware: OLED Shield: SSD1306, 64x48 pixel, I2C
#ifndef D1_CLASS_DISPLAYKH_H
#define D1_CLASS_DISPLAYKH_H
#include <Wire.h>
//#include <Adafruit_SSD1306.h>          // use with Adafruit-lib
//#include <Adafruit_GFX.h>              // use with Adafruit-lib
#include "libs/Adafruit_SSD1306.h"     // use with /libs
#include "libs/Adafruit_GFX.h"         // use with /libs
#ifndef OLED_RESET
 #define OLED_RESET D3            // OLED_RESET=D3=GPIO0
#endif

extern const uint8_t fontKH_5x8Bitmaps[] PROGMEM;
extern const GFXfont fontKH_5x8 PROGMEM;

class DisplayKH : public Adafruit_SSD1306 {
public:
 DisplayKH();
 void screen6 (int line_, String text_, char align_, bool cls_);
 void screen6i(int line_, String text_, char align_, bool cls_);
 void screen5 (int line_, String text_, char align_, bool cls_);
 void screen5i(int line_, String text_, char align_, bool cls_);
 void screen4 (int line_, String text_, char align_, bool cls_);
 void screen4i(int line_, String text_, char align_, bool cls_);
 void screen4ii(int line_,String text_, char align_, bool cls_);
 void screen221(int line_,String text_, char align_, bool cls_);
 //-----screens with big character-lines------------------------
 void screen112(int line_,String text_, char align_, bool cls_);
 void screen13(int line_, String text_, char align_, bool cls_);
 void screen12(int line_, String text_, char align_, bool cls_);
 void screen2 (int line_, String text_, char align_, bool cls_); 
private:
 String mytrim(int max_, String txt_, char align);
 void scr6(int line_, String text_, char align_, bool cls_, bool invert_);
 void scr5(int line_, String text_, char align_, bool cls_, bool invert_);
 void scr4(int line_, String text_, char align_, bool cls_, bool invert_);
};

//_____constructor______________________________________________
DisplayKH::DisplayKH() {
 Adafruit_SSD1306(OLED_RESET);
 this->begin(SSD1306_SWITCHCAPVCC, 0x3C);   //I2C addr 0x3C
 this->clearDisplay();                      //Clear display-buff
 this->setTextColor(WHITE);
 this->setFont(&fontKH_5x8);
 //this->setFont(NULL);
 this->setTextSize(1);
 this->display();                           //swow display-buff
}

//**************************************************************
// screens with only single size lines
//**************************************************************

//_____display: 1 area, 6 lines, 10 chars/line, no border_______
// align: l=left, c=center, r=right, L=left+overwrite, C, R...
void DisplayKH::screen6(int line_, String text_, 
  char align_='l', bool cls_=false)
{
 scr6(line_, text_, align_, cls_, false);
}

//_____display: 1 area, 6 lines, 10 chars/line, no border_______
// first line inverted
// align: l=left, c=center, r=right, L=left+overwrite, C, R...
void DisplayKH::screen6i(int line_, String text_, 
  char align_='l', bool cls_=false)
{
 scr6(line_, text_, align_, cls_, true);
}

//_____display: 1 area, 5 lines, 10 chars/line, border__________
// align: l=left, c=center, r=right, L=left+overwrite, C, R...
void DisplayKH::screen5(int line_, String text_, 
  char align_='l', bool cls_=false)
{
 scr5(line_, text_, align_, cls_, false);
}

//_____display: 1 area, 5 lines, 10 chars/line, border__________
// align: l=left, c=center, r=right, L=left+overwrite, C, R...
void DisplayKH::screen5i(int line_, String text_, 
  char align_='l', bool cls_=false)
{
 scr5(line_, text_, align_, cls_, true);
}

//_____display: 1 area, 4 lines, 10 chars/line, border__________
// align: l=left, c=center, r=right, L=left+overwrite, C, R...
void DisplayKH::screen4(int line_, String text_, 
  char align_='l', bool cls_=false)
{
 scr4(line_, text_, align_, cls_, false);
}

//_____display: 1 area, 4 lines, 10 chars/line, border__________
// align: l=left, c=center, r=right, L=left+overwrite, C, R...
void DisplayKH::screen4i(int line_, String text_, 
  char align_='l', bool cls_=false)
{
 scr4(line_, text_, align_, cls_, true);
}

//_____display: 1 area, 4 lines, 10 chars/line, border__________
// line 1 and 3 inverted
// align: l=left, c=center, r=right, L=left+overwrite, C, R...
void DisplayKH::screen4ii(int line_, String text_, 
  char align_='c', bool cls_=false)
{
 int dx=0;
 int max_=10;
 String s_=text_;
 int len_=s_.length();
 bool clr_=isLowerCase(align_);             //clear area before
 align_=tolower(align_);                    //only lower chars
 if(cls_) this->clearDisplay();             //clear buffer
 //-----write text----------------------------------------------
 switch(line_)
 {
  case 1: //-----area 1, line 1 or more-------------------------
   if(align_=='c'){ if((len_<max_) &&((len_&1)>0)) dx=3; }
   if(clr_) {
    this->fillRect(1,1,62,10,WHITE);       //clear line 1
   }
   this->setCursor(dx+3,2);                //
   this->setTextColor(BLACK,WHITE);
   this->print(mytrim(max_, s_, align_));  //write text
   this->setTextColor(WHITE,BLACK);
   if(len_<=max_) break;
   s_=s_.substring(max_);
   len_=s_.length();
  case 2: //-----area 1, line 2 or more-------------------------
   if(align_=='c'){ if((len_<max_) &&((len_&1)>0)) dx=3; }
   if(clr_)this->fillRect(1,11,62,12,BLACK);//clear line 2
   this->setCursor(dx+3,13);                //
   this->print(mytrim(max_, s_, align_));   //write text
   if(len_<=max_) break;
   s_=s_.substring(max_);
   len_=s_.length();
  case 3: //-----area 1, line 3 or more-------------------------
   if(align_=='c'){ if((len_<max_) &&((len_&1)>0)) dx=3; }
   if(clr_) {
    this->fillRect(1,24,62,11,WHITE);      //clear line 1
   }
   this->setCursor(dx+3,26);               //
   this->setTextColor(BLACK,WHITE);
   this->print(mytrim(max_, s_, align_));  //write text
   this->setTextColor(WHITE,BLACK);
   if(len_<=max_) break;
   s_=s_.substring(max_);
   len_=s_.length();
  case 4: //-----area 1, line 4 or more-------------------------
   if(align_=='c'){ if((len_<max_) &&((len_&1)>0)) dx=3; }
   if(clr_)this->fillRect(1,35,62,12,BLACK);//clear line 4
   this->setCursor(dx+3,37);                //
   this->print(mytrim(max_, s_, align_));   //write text
   break;
  default: break;
 }
 this->drawRect(0,0,64,48,WHITE);           // border
 this->display();                           //show buffer
}

//_____display: 3 areas, 5 lines, 10 chars/line, borders________
// border around area 1 and 2
// align: l=left, c=center, r=right, L=left+overwrite, C, R...
void DisplayKH::screen221(int line_, String text_, 
  char align_='l', bool cls_=false)
{
 int dx=0;
 int max_=10;
 String s_=text_;
 int len_=s_.length();
 bool clr_=isLowerCase(align_);   //clear area before writing
 align_=tolower(align_);
 if(cls_) this->clearDisplay();
 //-----write text----------------------------------------------
 switch(line_)
 {
  case 1: //-----area 1, line 1 or more-------------------------
   if(align_=='c'){ if((len_<max_) &&((len_&1)>0)) dx=3; }
   if(clr_) this->fillRect(1,1,62,9,BLACK); //clear line 1
   this->setCursor(dx+2,2);                 //
   this->print(mytrim(max_, s_, align_));   //write text
   if(len_<=max_) break;
   s_=s_.substring(max_);
   len_=s_.length();
   case 2: //-----area 1, line 2--------------------------------
   if(align_=='c'){ if((len_<max_) &&((len_&1)>0)) dx=3; }
   if(clr_) this->fillRect(1,10,62,8,BLACK);//clear line 2
   this->setCursor(dx+2,10);                //
   this->print(mytrim(max_, s_, align_));   //write text
   break;
  case 3: //-----area 2, line 3 or more-------------------------
   if(align_=='c'){ if((len_<max_) &&((len_&1)>0)) dx=3; }
   if(clr_) this->fillRect(1,19,62,9,BLACK);//clear line 3
   this->setCursor(dx+2,20);                //
   this->print(mytrim(max_, s_, align_));   //write text
   if(len_<=max_) break;
   s_=s_.substring(max_);
   len_=s_.length();
   case 4: //-----area 2, line 4--------------------------------
   if(align_=='c'){ if((len_<max_) &&((len_&1)>0)) dx=3; }
   if(clr_)this->fillRect(1,28,62,10,BLACK);//clear line 4
   this->setCursor(dx+2,29);                //
   this->print(mytrim(max_, s_, align_));   //write text
   break;  
  case 5: //-----area 3, one line out of the rectangle----------
   if(align_=='c'){ if((len_<max_) &&((len_&1)>0)) dx=3; }
   if(clr_) this->fillRect(0,39,64,9,BLACK);//clear line 5
   this->setCursor(dx,40);                  //dx only!
   this->print(mytrim(max_, s_, align_));   //write text
   break;
  default: break;
 }
 //-----draw lines----------------------------------------------
 this->drawRect(0,0,64,39,WHITE);      // border around line 1-4
 this->drawLine(1,18,62,18,WHITE);     // horizontal line
 this->display();                      // show buffer
}

//**************************************************************
// screens with single and double size lines
//**************************************************************

//_____display: 3 areas, 1+1+2 lines, 10/5/10 chars/line________
// area 1: inverted, area 2: double text size
// align: l=left, c=center, r=right, L=left+overwrite, C, R...
void DisplayKH::screen112(int line_, String text_, 
  char align_='c', bool cls_=false)
{
 int dx=0;
 int max_=10;
 String s_=text_;
 int len_=s_.length();
 bool clr_=isLowerCase(align_);   //clear area before writing
 align_=tolower(align_);
 if(cls_) this->clearDisplay();
 //-----write text----------------------------------------------
 switch(line_)
 {
   case 1: //-----area 1, line 1, inverted----------------------
   if(align_=='c'){ if((len_<max_) &&((len_&1)>0)) dx=3; }
   if(clr_) this->fillRect(0,0,64,10,WHITE);//clear line 1
   this->setCursor(dx+2,1);                 //
   this->setTextColor(BLACK,WHITE);
   this->print(mytrim(max_, s_, align_));   //write text
   this->setTextColor(WHITE,BLACK);
   break; 
  case 2: //-----area 2, double text size-----------------------
   max_=5;
   if(align_=='c'){ if((len_<max_) &&((len_&1)==0)) dx=6; }
   if(clr_)this->fillRect(1,10,62,19,BLACK);//clear area 2 
   this->setCursor(dx+3,12);
   this->setTextSize(2);                    //charsize 10x16 pix
   this->println(mytrim(max_, text_, align_));   //write line 1  
   this->setTextSize(1);                    //charsize 5x8 pixel
   break;
  case 3: //-----area 3, line 1 or more-------------------------
   if(align_=='c'){ if((len_<max_) &&((len_&1)>0)) dx=3; }
   if(clr_)this->fillRect(0,29,64,11,BLACK);//clear line 3
   this->setCursor(dx,31);                  //
   this->print(mytrim(max_, s_, align_));   //write text
   if(len_<=max_) break;
   s_=s_.substring(max_);
   len_=s_.length();
   case 4: //-----area 3, line 2--------------------------------
   if(align_=='c'){ if((len_<max_) &&((len_&1)>0)) dx=3; }
   if(clr_) this->fillRect(0,40,64,8,BLACK);//clear line 4
   this->setCursor(dx,40);                  //
   this->print(mytrim(max_, s_, align_));   //write text
   break;  
  default: break;
 }
 //-----draw lines----------------------------------------------
 this->drawRect(0,0,64,30,WHITE);      // border around area 1
 this->display();                      // show buffer
}

//_____display: 2 areas: 1/3 lines, 5/10 chars/line_____________
// align: l=left, c=center, r=right, L=left+overwrite, C, R...
void DisplayKH::screen13(int line_, String text_, 
  char align_='c', bool cls_=false)
{
 int dx=0;
 int max_=10;
 String s_=text_;
 int len_=s_.length();
 bool clr_=isLowerCase(align_);   // clear area before writing
 align_=tolower(align_);
 if(cls_) this->clearDisplay();
 //-----write text----------------------------------------------
 switch(line_)
 {
  case 1: //-----area 1, double text size-----------------------
   max_=5;
   if(align_=='c'){ if((len_<max_) &&((len_&1)==0)) dx=6; }
   if(clr_) this->fillRect(1,1,62,19,BLACK);     //clear area 1 
   this->setCursor(dx+3,3);
   this->setTextSize(2);                    //charsize 10x16 pix
   this->println(mytrim(max_, text_, align_));   //write line 1  
   this->setTextSize(1);                    //charsize 5x8 pixel
   break;
  case 2: //-----area 2, line 2 or more-------------------------
   if(align_=='c'){ if((len_<max_) &&((len_&1)>0)) dx=3; }
   if(clr_)this->fillRect(0,21,64,10,BLACK);//clear line 2
   this->setCursor(dx,22);                  //
   this->print(mytrim(max_, s_, align_));   //write text
   if(len_<=max_) break;
   s_=s_.substring(max_);
   len_=s_.length();  
  case 3: //-----area 2, line 3 or more-------------------------
   if(align_=='c'){ if((len_<max_) &&((len_&1)>0)) dx=3; }
   if(clr_)this->fillRect(0,30,64,10,BLACK);//clear line 3
   this->setCursor(dx,31);                  //
   this->print(mytrim(max_, s_, align_));   //write text
   if(len_<=max_) break;
   s_=s_.substring(max_);
   len_=s_.length();  
  case 4: //-----area 2, line 4---------------------------------
   if(align_=='c'){ if((len_<max_) &&((len_&1)>0)) dx=3; }
   if(clr_) this->fillRect(0,40,64,8,BLACK);//clear line 4
   this->setCursor(dx,40);                  //
   this->print(mytrim(max_, s_, align_));   //write text
   break; 
  default: break;
 }
 //-----draw lines----------------------------------------------
 this->drawRect(0,0,64,21,WHITE);      // border around area 1
 this->display();                      // show buffer
}

//_____display: 2 areas, 1+2 lines, 5/10 chars/line, border_____
// area 1: double text size
// align: l=left, c=center, r=right, L=left+overwrite, C, R...
void DisplayKH::screen12(int line_, String text_, 
  char align_='c', bool cls_=false)
{
 int dx=0;
 int max_=10;
 String s_=text_;
 int len_=s_.length();
 bool clr_=isLowerCase(align_);   // clear area before writing
 align_=tolower(align_);
 if(cls_) this->clearDisplay();
 //-----write text----------------------------------------------
 switch(line_)
 {
  case 1: //-----area 1, double text size-----------------------
   max_=5;
   if(align_=='c'){ if((len_<max_) &&((len_&1)==0)) dx=6; }
   if(clr_) this->fillRect(1,1,62,27,BLACK);     //clear area 1 
   this->setCursor(dx+3,7);
   this->setTextSize(2);                    //charsize 10x16 pix
   this->println(mytrim(max_, text_, align_));   //write line 1  
   this->setTextSize(1);                    //charsize 5x8 pixel
   break;
  case 2: //-----area 2, line 2 or more-------------------------
   if(align_=='c'){ if((len_<max_) &&((len_&1)>0)) dx=3; }
   if(clr_) this->fillRect(0,29,64,19,BLACK);//clear line 2
   this->setCursor(dx,31);                   //
   this->print(mytrim(max_, s_, align_));   //write text
   if(len_<=max_) break;
   s_=s_.substring(max_);
   len_=s_.length();
   case 3: //-----area 2, line 3--------------------------------
   if(align_=='c'){ if((len_<max_) &&((len_&1)>0)) dx=3; }
   if(clr_) this->fillRect(0,40,64,8,BLACK);//clear line 4
   this->setCursor(dx,40);                   //
   this->print(mytrim(max_, s_, align_));   //write text
   break;  
  default: break;
 }
 //-----draw lines----------------------------------------------
 this->drawRect(0,0,64,29,WHITE);      // border around area 1
 this->display();                      // show buffer
}

//_____display: 1 area, 2 lines, 5 chars/line, border___________
// align: l=left, c=center, r=right, L=left+overwrite, C, R...
void DisplayKH::screen2(int line_, String text_, 
  char align_='c', bool cls_=false)
{
 int dx=0;
 int max_=5;
 String s_=text_;
 int len_=s_.length();
 bool clr_=isLowerCase(align_);             //clear area before
 align_=tolower(align_);                    //only lower chars
 if(cls_) this->clearDisplay();             //clear buffer
 this->setTextSize(2);                      //char size 10x16px
 //-----write text----------------------------------------------
 switch(line_)
 {
  case 1: //-----area 1, line 1, double text size---------------
   if(align_=='c'){ if((len_<max_) &&((len_&1)==0)) dx=6; }
   if(clr_) this->fillRect(1,1,62,25,BLACK);//clear line 1
   this->setCursor(dx+3+dx,7);              //
   this->print(mytrim(max_, s_, align_));   //write text
   if(len_<=max_) break;
   s_=s_.substring(max_);
   len_=s_.length();
  case 2: //-----area 1, line 2 or more-------------------------
   if(align_=='c'){ if((len_<max_) &&((len_&1)>0)) dx=3; }
   if(clr_)this->fillRect(1,26,62,22,BLACK);//clear line 2
   this->setCursor(dx+3+dx,26);             //
   this->print(mytrim(max_, s_, align_));   //write text
   if(len_<=max_) break;
  default: break;
 }
 this->setTextSize(1);                      //charsize 5x8 pixel
 this->drawRect(0,0,64,48,WHITE);           // border
 this->display();                           //show buffer
}

//**************************************************************
// helper functions
//**************************************************************

//_____make string with max chars (add blank before/after)______
String DisplayKH::mytrim(int max_, String txt_, char align_='l')
{
 String s=txt_;
 //-----add leading blanks, if align_ needs them----------------
 int blank_=0;
 int len_=s.length();
 if(align_=='c') blank_=(max_-len_)/2;
 if(align_=='r') { if(len_<max_) blank_=max_-len_; }
 //-----add blanks before text----------------------------------
 for(int i=0; i<blank_; i++) s=" "+s;
 if(len_>max_) 
 { //-----text too long, truncate text--------------------------
  s=s.substring(0,max_);
 }
 else //-----text too short, add blank--------------------------
 {
  for(int i=len_; i<max_; i++) s+=" ";
 }
 return s;
}

//_____display: 1 area, 6 lines, 10 chars/line, no border_______
// first line may be inverted
// align: l=left, c=center, r=right, L=left+overwrite, C, R...
void DisplayKH::scr6(int line_, String text_, 
  char align_, bool cls_, bool invert_)
{
 int dx=0;
 int max_=10;
 String s_=text_;
 int len_=s_.length();
 bool clr_=isLowerCase(align_);             //clear area before
 align_=tolower(align_);                    //only lower chars
 if(cls_) this->clearDisplay();             //clear buffer
 //-----write text----------------------------------------------
 switch(line_)
 {
  case 1: //-----area 1, line 1 or more-------------------------
   if(align_=='c'){ if((len_<max_) &&((len_&1)>0)) dx=3; }
   if(clr_) {
    if(invert_) this->fillRect(0,0,64,8,WHITE);  //clear line 1
           else this->fillRect(0,0,64,8,BLACK);  //clear line 1
   }
   this->setCursor(dx,0);                   //
   if(invert_) this->setTextColor(BLACK,WHITE);
   this->print(mytrim(max_, s_, align_));   //write text
   if(invert_) this->setTextColor(WHITE,BLACK);
   if(len_<=max_) break;
   s_=s_.substring(max_);
   len_=s_.length();
  case 2: //-----area 1, line 2 or more-------------------------
   if(align_=='c'){ if((len_<max_) &&((len_&1)>0)) dx=3; }
   if(clr_) this->fillRect(0,8,64,8,BLACK); //clear line 2
   this->setCursor(dx,8);                   //
   this->print(mytrim(max_, s_, align_));   //write text
   if(len_<=max_) break;
   s_=s_.substring(max_);
   len_=s_.length();
  case 3: //-----area 1, line 3 or more-------------------------
   if(align_=='c'){ if((len_<max_) &&((len_&1)>0)) dx=3; }
   if(clr_) this->fillRect(0,16,64,8,BLACK);//clear line 3
   this->setCursor(dx,16);                  //
   this->print(mytrim(max_, s_, align_));   //write text
   if(len_<=max_) break;
   s_=s_.substring(max_);
   len_=s_.length();
  case 4: //-----area 1, line 4 or more-------------------------
   if(align_=='c'){ if((len_<max_) &&((len_&1)>0)) dx=3; }
   if(clr_) this->fillRect(0,24,64,8,BLACK);//clear line 4
   this->setCursor(dx,24);                  //
   this->print(mytrim(max_, s_, align_));   //write text
   if(len_<=max_) break;
   s_=s_.substring(max_);
   len_=s_.length();  
  case 5: //-----area 1, line 5 or more-------------------------
   if(align_=='c'){ if((len_<max_) &&((len_&1)>0)) dx=3; }
   if(clr_) this->fillRect(0,32,64,8,BLACK);//clear line 5
   this->setCursor(dx,32);                  //
   this->print(mytrim(max_, s_, align_));   //write text
   if(len_<=max_) break;
   s_=s_.substring(max_);
   len_=s_.length();  
  case 6: //-----area 1, line 6---------------------------------
   if(align_=='c'){ if((len_<max_) &&((len_&1)>0)) dx=3; }
   if(clr_) this->fillRect(0,40,64,8,BLACK);//clear line 6
   this->setCursor(dx,40);                  //
   this->print(mytrim(max_, s_, align_));   //write text
   break;
  default: break;
 }
 this->display();                           //show buffer
}

//_____display: 1 area, 5 lines, 10 chars/line, border__________
// first line may be inverted
// align: l=left, c=center, r=right, L=left+overwrite, C, R...
void DisplayKH::scr5(int line_, String text_, 
  char align_, bool cls_, bool invert_)
{
 int dx=0;
 int max_=10;
 String s_=text_;
 int len_=s_.length();
 bool clr_=isLowerCase(align_);             //clear area before
 align_=tolower(align_);                    //only lower chars
 if(cls_) this->clearDisplay();             //clear buffer
 //-----write text----------------------------------------------
 switch(line_)
 {
  case 1: //-----area 1, line 1 or more-------------------------
   if(align_=='c'){ if((len_<max_) &&((len_&1)>0)) dx=3; }
   if(clr_) {
    if(invert_) this->fillRect(1,1,62,10,WHITE); //clear line 1
           else this->fillRect(1,1,62,10,BLACK); //clear line 1
   }
   this->setCursor(dx+3,2);                 //
   if(invert_) this->setTextColor(BLACK,WHITE);
   this->print(mytrim(max_, s_, align_));   //write text
   if(invert_) this->setTextColor(WHITE,BLACK);
   if(len_<=max_) break;
   s_=s_.substring(max_);
   len_=s_.length();
  case 2: //-----area 1, line 2 or more-------------------------
   if(align_=='c'){ if((len_<max_) &&((len_&1)>0)) dx=3; }
   if(clr_) this->fillRect(1,11,62,9,BLACK);//clear line 2
   this->setCursor(dx+3,11);                //
   this->print(mytrim(max_, s_, align_));   //write text
   if(len_<=max_) break;
   s_=s_.substring(max_);
   len_=s_.length();
  case 3: //-----area 1, line 3 or more-------------------------
   if(align_=='c'){ if((len_<max_) &&((len_&1)>0)) dx=3; }
   if(clr_) this->fillRect(1,20,62,9,BLACK);//clear line 3
   this->setCursor(dx+3,20);                //
   this->print(mytrim(max_, s_, align_));   //write text
   if(len_<=max_) break;
   s_=s_.substring(max_);
   len_=s_.length();
  case 4: //-----area 1, line 4 or more-------------------------
   if(align_=='c'){ if((len_<max_) &&((len_&1)>0)) dx=3; }
   if(clr_) this->fillRect(1,29,62,9,BLACK);//clear line 4
   this->setCursor(dx+3,29);                //
   this->print(mytrim(max_, s_, align_));   //write text
   if(len_<=max_) break;
   s_=s_.substring(max_);
   len_=s_.length();  
  case 5: //-----area 1, line 5---------------------------------
   if(align_=='c'){ if((len_<max_) &&((len_&1)>0)) dx=3; }
   if(clr_) this->fillRect(1,38,62,9,BLACK);//clear line 5
   this->setCursor(dx+3,38);                //
   this->print(mytrim(max_, s_, align_));   //write text
   break;
  default: break;
 }
 this->drawRect(0,0,64,48,WHITE);           // border
 this->display();                           //show buffer
}

//_____display: 1 area, 4 lines, 10 chars/line, border__________
// align: l=left, c=center, r=right, L=left+overwrite, C, R...
void DisplayKH::scr4(int line_, String text_, 
  char align_, bool cls_, bool invert_)
{
 int dx=0;
 int max_=10;
 String s_=text_;
 int len_=s_.length();
 bool clr_=isLowerCase(align_);             //clear area before
 align_=tolower(align_);                    //only lower chars
 if(cls_) this->clearDisplay();             //clear buffer
 //-----write text----------------------------------------------
 switch(line_)
 {
  case 1: //-----area 1, line 1 or more-------------------------
   if(align_=='c'){ if((len_<max_) &&((len_&1)>0)) dx=3; }
   if(invert_)
   {
    if(clr_) {
     this->fillRect(1,1,62,12,WHITE);       //clear line 1
     this->drawLine(1,12,62,12,BLACK);      // horizontal line
    }
    this->setCursor(dx+3,2);                //
    this->setTextColor(BLACK,WHITE);
    this->print(mytrim(max_, s_, align_));  //write text
    this->setTextColor(WHITE,BLACK);
   }
   else
   {
    if(clr_)this->fillRect(1,1,62,13,BLACK);//clear line 1
    this->setCursor(dx+3,4);                //
    this->print(mytrim(max_, s_, align_));  //write text
   }
   if(len_<=max_) break;
   s_=s_.substring(max_);
   len_=s_.length();
  case 2: //-----area 1, line 2 or more-------------------------
   if(align_=='c'){ if((len_<max_) &&((len_&1)>0)) dx=3; }
   if(clr_)this->fillRect(1,14,62,12,BLACK);//clear line 2
   this->setCursor(dx+3,15);                //
   this->print(mytrim(max_, s_, align_));   //write text
   if(len_<=max_) break;
   s_=s_.substring(max_);
   len_=s_.length();
  case 3: //-----area 1, line 3 or more-------------------------
   if(align_=='c'){ if((len_<max_) &&((len_&1)>0)) dx=3; }
   if(clr_)this->fillRect(1,26,62,11,BLACK);//clear line 3
   this->setCursor(dx+3,26);                //
   this->print(mytrim(max_, s_, align_));   //write text
   if(len_<=max_) break;
   s_=s_.substring(max_);
   len_=s_.length();
  case 4: //-----area 1, line 4 or more-------------------------
   if(align_=='c'){ if((len_<max_) &&((len_&1)>0)) dx=3; }
   if(clr_)this->fillRect(1,37,62,11,BLACK);//clear line 4
   this->setCursor(dx+3,37);                //
   this->print(mytrim(max_, s_, align_));   //write text
   break;
  default: break;
 }
 this->drawRect(0,0,64,48,WHITE);           // border
 this->display();                           //show buffer
}

//**************************************************************
// font
//**************************************************************

const uint8_t fontKH_5x8Bitmaps[] PROGMEM = {
 0x00, 0x00, 0x00, 0x00, 0x00, // 0x20 ' '
 0x21, 0x08, 0x42, 0x00, 0x80, // 0x21 '!'	
 0x52, 0x94, 0x00, 0x00, 0x00, // 0x22 '"'
 0x52, 0xBE, 0xAF, 0xA9, 0x40, // 0x23 '#'
 0x23, 0xE8, 0xE2, 0xF8, 0x80, // 0x24 '$'
 0xC6, 0x44, 0x44, 0x4C, 0x60, // 0x25 '%'
 0x45, 0x28, 0x8A, 0xC9, 0xA0, // 0x26 '&'
 0x31, 0x88, 0x80, 0x00, 0x00, // 0x27 '''
 0x11, 0x10, 0x84, 0x10, 0x40, // 0x28 '('
 0x41, 0x04, 0x21, 0x11, 0x00, // 0x29 ')'
 0x25, 0x5D, 0xF7, 0x54, 0x80, // 0x2A '*' 
 0x01, 0x09, 0xF2, 0x10, 0x00, // 0x2B '+'
 0x00, 0x00, 0x03, 0x18, 0x88, // 0x2C ','
 0x00, 0x01, 0xF0, 0x00, 0x00, // 0x2D '-'
 0x00, 0x00, 0x00, 0x18, 0x80, // 0x2E '.'
 0x00, 0x44, 0x44, 0x40, 0x00, // 0x2F '/'
 0x74, 0x67, 0x5C, 0xC5, 0xC0, // 0x30 '0'
 0x23, 0x08, 0x42, 0x11, 0xC0, // 0x21 '1'
 0x78, 0x42, 0xE8, 0x43, 0xE0, // 0x32 '2'
 0xF8, 0x44, 0x60, 0xC5, 0xC0, // 0x33 '3'
 0x11, 0x95, 0x2F, 0x88, 0x40, // 0x34 '4'
 0xFC, 0x3C, 0x10, 0xC5, 0xC0, // 0x35 '5'
 0x3A, 0x21, 0xE8, 0xC5, 0xC0, // 0x36 '6'
 0xF8, 0x42, 0x22, 0x22, 0x00, // 0x37 '7'
 0x74, 0x62, 0xE8, 0xC5, 0xC0, // 0x38 '8'
 0x74, 0x62, 0xF0, 0x8B, 0x80, // 0x39 '9'
 0x00, 0x08, 0x02, 0x00, 0x00, // 0x3A ':'
 0x00, 0x08, 0x02, 0x11, 0x08, // 0x3B ';'
 0x08, 0x88, 0x82, 0x08, 0x20, // 0x3C '<'
 0x00, 0x3E, 0x0F, 0x80, 0x00, // 0x3D '='
 0x41, 0x04, 0x11, 0x11, 0x00, // 0x3E '>'
 0x74, 0x42, 0x62, 0x00, 0x80, // 0x3F '?'
 0x74, 0x6B, 0x7B, 0x41, 0xE0, // 0x40 '@'
 0x22, 0xA3, 0x1F, 0xC6, 0x20, // 0x41 'A'
 0xF4, 0x63, 0xE8, 0xC7, 0xC0, // 0x42 'B'
 0x74, 0x61, 0x08, 0x45, 0xC0, // 0x43 'C'
 0xF4, 0x63, 0x18, 0xC7, 0xC0, // 0x44 'D'
 0xFC, 0x21, 0xE8, 0x43, 0xE0, // 0x45 'E'
 0xFC, 0x21, 0xE8, 0x42, 0x00, // 0x46 'F'
 0x7C, 0x61, 0x09, 0xC5, 0xE0, // 0x47 'G'
 0x8C, 0x63, 0xF8, 0xC6, 0x20, // 0x48 'H'
 0x71, 0x08, 0x42, 0x11, 0xC0, // 0x49 'I'
 0x38, 0x84, 0x21, 0x49, 0x80, // 0x4A 'J'
 0x8C, 0xA9, 0x8A, 0x4A, 0x20, // 0x4B 'K'
 0x84, 0x21, 0x08, 0x43, 0xE0, // 0x4C 'L'
 0x8E, 0xEB, 0x5A, 0xC6, 0x20, // 0x4D 'M'
 0x8C, 0x73, 0x59, 0xC6, 0x20, // 0x4E 'N'
 0x74, 0x63, 0x18, 0xC5, 0xC0, // 0x4F 'O'
 0xF4, 0x63, 0xE8, 0x42, 0x00, // 0x50 'P'
 0x74, 0x63, 0x1A, 0xC9, 0xA0, // 0x51 'Q'
 0xF4, 0x63, 0xEA, 0x4A, 0x20, // 0x52 'R'
 0x74, 0x60, 0xE0, 0xC5, 0xC0, // 0x53 'S'
 0xFD, 0x48, 0x42, 0x10, 0x80, // 0x54 'T'
 0x8C, 0x63, 0x18, 0xC5, 0xC0, // 0x55 'U'
 0x8C, 0x63, 0x18, 0xA8, 0x80, // 0x56 'V'
 0x8C, 0x63, 0x5A, 0xD5, 0x40, // 0x57 'W'
 0x8C, 0x54, 0x45, 0x46, 0x20, // 0x58 'X'
 0x8C, 0x54, 0x42, 0x10, 0x80, // 0x59 'Y'
 0xF8, 0x44, 0xE4, 0x43, 0xE0, // 0x5A 'Z'
 0x72, 0x10, 0x84, 0x21, 0xC0, // 0x5B '['
 0x04, 0x10, 0x41, 0x04, 0x00, // 0x5C '\'
 0x70, 0x84, 0x21, 0x09, 0xC0, // 0x5D ']'
 0x22, 0xA2, 0x00, 0x00, 0x00, // 0x5E '^'
 0x00, 0x00, 0x00, 0x03, 0xE0, // 0x5F '_'
 0x63, 0x08, 0x20, 0x00, 0x00, // 0x60 '`'
 0x00, 0x18, 0x27, 0x49, 0xE0, // 0x61 'a'
 0x84, 0x2D, 0x98, 0xE6, 0xC0, // 0x62 'b'
 0x00, 0x1D, 0x18, 0x45, 0xC0, // 0x63 'c'
 0x08, 0x5B, 0x38, 0xCD, 0xA0, // 0x64 'd'
 0x00, 0x1D, 0x1F, 0xC1, 0xC0, // 0x65 'e'
 0x11, 0x48, 0xE2, 0x10, 0x80, // 0x66 'f'
 0x00, 0x1D, 0x39, 0xB4, 0x2E, // 0x67 'g'
 0x84, 0x2D, 0x98, 0xC6, 0x20, // 0x68 'h'
 0x20, 0x18, 0x42, 0x11, 0xC0, // 0x69 'i'
 0x10, 0x04, 0x21, 0x49, 0x80, // 0x6A 'j'
 0x84, 0x25, 0x4C, 0x52, 0x40, // 0x6B 'k'
 0x61, 0x08, 0x42, 0x11, 0xC0, // 0x6C 'l'
 0x00, 0x35, 0x5A, 0xD6, 0xA0, // 0x6D 'm'
 0x00, 0x2D, 0x98, 0xC6, 0x20, // 0x6E 'n'
 0x00, 0x1D, 0x18, 0xC5, 0xC0, // 0x6F 'o'
 0x00, 0x2D, 0x9C, 0xDA, 0x10, // 0x70 'p'
 0x00, 0x1B, 0x39, 0xB4, 0x21, // 0x71 'q'
 0x00, 0x2D, 0x98, 0x42, 0x00, // 0x72 'r'
 0x00, 0x1F, 0x07, 0x07, 0xC0, // 0x73 's'
 0x21, 0x3E, 0x42, 0x14, 0x40, // 0x74 't'
 0x00, 0x23, 0x18, 0xCD, 0xA0, // 0x75 'u'
 0x00, 0x23, 0x18, 0xA8, 0x80, // 0x76 'v'
 0x00, 0x23, 0x1A, 0xD5, 0x40, // 0x77 'w'
 0x00, 0x22, 0xA2, 0x2A, 0x20, // 0x78 'x'
 0x00, 0x23, 0x17, 0x86, 0x2E, // 0x79 'y'
 0x00, 0x3E, 0x22, 0x23, 0xE0, // 0x7A 'z'
 0x11, 0x08, 0x82, 0x10, 0x40, // 0x7B '{'
 0x21, 0x08, 0x02, 0x10, 0x80, // 0x7C '|'
 0x41, 0x08, 0x22, 0x11, 0x00, // 0x7D '}'
 0x45, 0x44, 0x00, 0x00, 0x00, // 0x7E '~'
 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // 0x7F = 127 '�'
 0x32, 0x78, 0x8E, 0x24, 0xC0, // 0x80 = 128 '�'
 0x50, 0x23, 0x18, 0xCD, 0xA0, // 0x81 = 129 '��'
 0x18, 0x1D, 0x1F, 0xC1, 0xE0, // 0x82 = 130 '�'
 0xF8, 0x18, 0x27, 0x49, 0xE0, // 0x83 = 131 '�'
 0x50, 0x18, 0x27, 0x49, 0xE0, // 0x84 = 132 '�'
 0xC0, 0x18, 0x27, 0x49, 0xE0, // 0x85 = 133 '�'
 0x20, 0x18, 0x27, 0x49, 0xE0, // 0x86 = 134 '�'
 0x03, 0xF1, 0x87, 0x88, 0xC0, // 0x87 = 135 '�'
 0xF8, 0x1D, 0x1F, 0xC1, 0xE0, // 0x88 = 136 '�'
 0x88, 0x1D, 0x1F, 0xC1, 0xE0, // 0x89 = 137 '�'
 0xC0, 0x1D, 0x1F, 0xC1, 0xE0, // 0x8A = 138 '�'
 0x50, 0x18, 0x42, 0x11, 0xC0, // 0x8B = 139 '�'
 0x64, 0x80, 0xC2, 0x11, 0xC0, // 0x8C = 140 '�'
 0xC0, 0x18, 0x42, 0x11, 0xC0, // 0x8D = 141 '��'
 0x89, 0x15, 0x1F, 0xC6, 0x20, // 0x8E = 142 '�'
 0x20, 0x08, 0xA8, 0xFE, 0x20, // 0x8F = 143 '��'
 0x30, 0x3D, 0x0E, 0x43, 0xC0, // 0x90 = 144 '�'
 0x00, 0x3C, 0x57, 0x51, 0xE0, // 0x91 = 145 '�'
 0x3A, 0xA5, 0xF9, 0x4A, 0x60, // 0x92 = 146 '�'
 0x22, 0x80, 0xE8, 0xC5, 0xC0, // 0x93 = 147 '�'
 0x50, 0x1D, 0x18, 0xC5, 0xC0, // 0x94 = 148 '�'
 0x06, 0x00, 0xE8, 0xC5, 0xC0, // 0x95 = 149 '�'
 0x22, 0x81, 0x18, 0xCD, 0xA0, // 0x96 = 150 '�'
 0x06, 0x01, 0x18, 0xCD, 0xA0, // 0x97 = 151 '�'
 0x48, 0x12, 0x94, 0x9C, 0x2E, // 0x98 = 152 '��'
 0x8B, 0xA3, 0x18, 0xC5, 0xC0, // 0x99 = 153 '�'
 0x88, 0x23, 0x18, 0xC5, 0xC0, // 0x9A = 154 '�'
 0x01, 0x1D, 0x5A, 0xB8, 0x80, // 0x9B = 155 '�'
 0x32, 0xD3, 0xC4, 0x23, 0xE0, // 0x9C = 156 '�'
 0xDE, 0xDD, 0xF2, 0x7C, 0x84, // 0x9D = 157 ' ' //'�'
 0xE4, 0xA5, 0xC9, 0x5E, 0x52, // 0x9E = 158 Pt  //'�'
 0x19, 0x48, 0xE2, 0x12, 0x98, // 0x9F = 159 '�'
 0x18, 0x18, 0x27, 0x49, 0xE0, // 0xA0 = 160 '�'
 0x18, 0x0C, 0x21, 0x08, 0xE0, // 0xA1 = 161 '�'
 0x00, 0xC0, 0xE8, 0xC5, 0xC0, // 0xA2 = 162 '�'
 0x00, 0xC1, 0x18, 0xCD, 0xA0, // 0xA3 = 163 '�'
 0x03, 0xC0, 0xE4, 0xA5, 0x20, // 0xA4 = 164 '�'
 0xF8, 0x33, 0xDB, 0xCE, 0x20, // 0xA5 = 165 '�'
 0x74, 0xA4, 0xF0, 0x7C, 0x00, // 0xA6 = 166 '�'
 0x74, 0x62, 0xE0, 0x7C, 0x00, // 0xA7 = 167 '�'
 0x20, 0x08, 0xC8, 0x45, 0xC0, // 0xA8 = 168 '�'
 0x00, 0x00, 0x0F, 0xC0, 0x00, // 0xA9 = 169 ' ' //'�'
 0x00, 0x00, 0x0F, 0x84, 0x00, // 0xAA = 170 '�' //'�'
 0x84, 0x64, 0x45, 0xE4, 0x47, // 0xAB = 171 1/2 //'�'
 0x84, 0x65, 0x55, 0xDC, 0x21, // 0xAC = 172 1/4 //'�'
 0x21, 0x00, 0x42, 0x10, 0x80, // 0xAD = 173 '|' //'�'
 0x01, 0x55, 0x45, 0x14, 0x00, // 0xAE = 174 '�' //'�'
 0x05, 0x14, 0x55, 0x50, 0x00, // 0xAF = 175 '�' //'�'
 0x55, 0x55, 0x55, 0x55, 0x55, // 0xB0 = 176     //'�'
 0xFD, 0x7F, 0x5F, 0xD7, 0xF5, // 0xB1 = 177     //'�'
 0x10, 0x84, 0x21, 0x08, 0x42, // 0xB2 = 178     //'�'
 0x10, 0x84, 0x2F, 0x08, 0x42, // 0xB3 = 179     //'�'
 0x10, 0xBC, 0x2F, 0x08, 0x42, // 0xB4 = 180     //'�'
 0x29, 0x4A, 0x5E, 0x94, 0xA5, // 0xB5 = 181     //'�'
 0x00, 0x00, 0x0F, 0x94, 0xA5, // 0xB6 = 182     //'�'
 0x00, 0x3E, 0x1F, 0x84, 0x21, // 0xB7 = 183     //'�'
 0x29, 0x7A, 0x1E, 0x94, 0xA5, // 0xB8 = 184     //'�'
 0x29, 0x4A, 0x52, 0x94, 0xA5, // 0xB9 = 185     //'�'
 0x00, 0x3E, 0x1E, 0x94, 0xA5, // 0xBA = 186     //'�'
 0x29, 0x7A, 0x1F, 0x80, 0x00, // 0xBB = 187     //'�'
 0x29, 0x4A, 0x5F, 0x80, 0x00, // 0xBC = 188     //'�'
 0x10, 0xBC, 0x2F, 0x00, 0x00, // 0xBD = 189     //'�'
 0x00, 0x00, 0x0F, 0x08, 0x42, // 0xBE = 190     //'�'
 0x10, 0x84, 0x21, 0x80, 0x00, // 0xBF = 191     //'�'
 0x10, 0x84, 0x2F, 0x80, 0x00, // 0xC0 = 192     //'�'
 0x00, 0x00, 0x0F, 0x88, 0x42, // 0xC1 = 193     //'�'
 0x10, 0x84, 0x21, 0x88, 0x42, // 0xC2 = 194     //'�'
 0x00, 0x00, 0x0F, 0x80, 0x00, // 0xC3 = 195     //'�'
 0x10, 0x84, 0x2F, 0x88, 0x42, // 0xC4 = 196     //'�'
 0x10, 0x86, 0x21, 0x88, 0x42, // 0xC5 = 197     //'�'
 0x29, 0x4A, 0x52, 0x94, 0xA5, // 0xC6 = 198     //'�'
 0x29, 0x4A, 0x43, 0x80, 0x00, // 0xC7 = 199     //'�'
 0x00, 0x0E, 0x42, 0x94, 0xA5, // 0xC8 = 200     //'�'
 0x29, 0x7A, 0x0F, 0x80, 0x00, // 0xC9 = 201     //'�'
 0x00, 0x3E, 0x0E, 0x94, 0xA5, // 0xCA = 202     //'�'
 0x29, 0x4A, 0x42, 0x94, 0xA5, // 0xCB = 203     //'�'
 0x00, 0x3E, 0x0F, 0x80, 0x00, // 0xCC = 204     //'�'
 0x29, 0x7A, 0x0E, 0x94, 0xA5, // 0xCD = 205     //'�'
 0x10, 0xBE, 0x0F, 0x80, 0x00, // 0xCE = 206     //'�'
 0x29, 0x4A, 0x5F, 0x80, 0x00, // 0xCF = 207     //'�'
 0x00, 0x3E, 0x0F, 0x88, 0x42, // 0xD0 = 208     //'�'
 0x00, 0x00, 0x0F, 0x94, 0xA5, // 0xD1 = 209     //'�'
 0x29, 0x4A, 0x53, 0x80, 0x00, // 0xD2 = 210     //'�'
 0x10, 0x86, 0x21, 0x80, 0x00, // 0xD3 = 211     //'�'
 0x00, 0x06, 0x21, 0x88, 0x42, // 0xD4 = 212     //'�'
 0x00, 0x00, 0x03, 0x94, 0xA5, // 0xD5 = 213     //'�'
 0x29, 0x4A, 0x5F, 0x94, 0xA5, // 0xD6 = 214     //'�'
 0x10, 0xBE, 0x2F, 0x88, 0x42, // 0xD7 = 215     //'�'
 0x10, 0x84, 0x2F, 0x00, 0x00, // 0xD8 = 216     //'�'
 0x00, 0x00, 0x01, 0x88, 0x42, // 0xD9 = 217     //'�'
 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // 0xDA = 218     //'�'
 0x00, 0x00, 0x0F, 0xFF, 0xFF, // 0xDB = 219     //'�'
 0xE7, 0x39, 0xCE, 0x73, 0x9C, // 0xDC = 220     //'�'
 0x18, 0xC6, 0x31, 0x8C, 0x63, // 0xDD = 221     //'�'
 0xFF, 0xFF, 0xF0, 0x00, 0x00, // 0xDE = 222     //'�'
 0x00, 0x1B, 0x29, 0x49, 0xA0, // 0xDF = 223     //'�'
 0x03, 0xA3, 0xE8, 0xC7, 0xD0, // 0xE0 = 224 '�' //'�'
 0xFC, 0xE1, 0x08, 0x42, 0x00, // 0xE1 = 225     //'�' .
 0x00, 0x3E, 0xA5, 0x2A, 0x60, // 0xE2 = 226 '�' //'�'
 0xFC, 0x50, 0x44, 0x47, 0xE0, // 0xE3 = 227     //'�'
 0x00, 0x1F, 0x29, 0x49, 0x80, // 0xE4 = 228     //'�'
 0x00, 0x14, 0xA5, 0x29, 0xB8, // 0xE5 = 229 '�' //'�'
 0x00, 0x1F, 0x42, 0x11, 0x80, // 0xE6 = 230     //
 0xF9, 0x1D, 0x5A, 0xB8, 0x9F, // 0xE7 = 231     //'�'
 0x22, 0xA3, 0xF8, 0xA8, 0x80, // 0xE8 = 232     //'�'
 0x22, 0xA3, 0x15, 0x2B, 0x60, // 0xE9 = 233     //'�'
 0x32, 0x0C, 0xE8, 0xC5, 0xC0, // 0xEA = 234     //'�'
 0x00, 0x17, 0x5D, 0x00, 0x00, // 0xEB = 235 unend.'�'
 0x0B, 0xA7, 0x5A, 0xE5, 0xD0, // 0xEC = 236     //'�'
 0x74, 0x21, 0xE8, 0x41, 0xC0, // 0xED = 237     //'�'
 0x74, 0x63, 0x18, 0xC6, 0x20, // 0xEE = 238     //'�'
 0x07, 0xC1, 0xF0, 0x7C, 0x00, // 0xEF = 239     //'�'
 0x21, 0x3E, 0x42, 0x03, 0xE0, // 0xF0 = 240 '�' //'�'
 0x41, 0x04, 0x44, 0x03, 0xE0, // 0xF1 = 241 >=  //'�'
 0x11, 0x10, 0x41, 0x03, 0xE0, // 0xF2 = 242 <=  //'�'
 0x39, 0x48, 0x42, 0x10, 0x80, // 0xF3 = 243     //'�'
 0x21, 0x08, 0x42, 0x52, 0x9C, // 0xF4 = 244     //'�'
 0x31, 0x81, 0xF0, 0x18, 0xC0, // 0xF5 = 245     //'�'
 0x07, 0x6E, 0x0E, 0xDC, 0x00, // 0xF6 = 246     //'�'
 0x32, 0x52, 0x60, 0x00, 0x00, // 0xF7 = 247 '�' //'�'
 0x00, 0x00, 0x63, 0x00, 0x00, // 0xF8 = 248 '�' //'�'
 0x00, 0x00, 0x03, 0x00, 0x00, // 0xF9 = 249     //'�'
 0x39, 0x08, 0x4A, 0x51, 0x84, // 0xFA = 250     //'�'
 0x72, 0x52, 0x94, 0x80, 0x00, // 0xFB = 251     //'�'
 0x32, 0x44, 0x47, 0x80, 0x00, // 0xFC = 252     //'�'
 0x00, 0x1E, 0xF7, 0xBC, 0x00, // 0xFD = 253     //'�'
 0x11, 0x11, 0x4B, 0x14, 0xA5, // 0xFE = 254     //'/h'
 0x00, 0x00, 0x00, 0x00, 0x00  // 0xFF = 255     //'�'
};

const GFXglyph fontKH_5x8Glyphs[] PROGMEM = {
 {   0,  5, 8,  6,  0, 0 },   // 0x20 ' '
 {   5,  5, 8,  6,  0, 0 },   // 0x21 '!'
 {  10,  5, 8,  6,  0, 0 },   // 0x22 '"'
 {  15,  5, 8,  6,  0, 0 },   // 0x23 '#'
 {  20,  5, 8,  6,  0, 0 },   // 0x24 '$'
 {  25,  5, 8,  6,  0, 0 },   // 0x25 '%'
 {  30,  5, 8,  6,  0, 0 },   // 0x26 '&'
 {  35,  5, 8,  6,  0, 0 },   // 0x27 '''
 {  40,  5, 8,  6,  0, 0 },   // 0x28 '('
 {  45,  5, 8,  6,  0, 0 },   // 0x29 ')'
 {  50,  5, 8,  6,  0, 0 },   // 0x2A '*'
 {  55,  5, 8,  6,  0, 0 },   // 0x2B '+'
 {  60,  5, 8,  6,  0, 0 },   // 0x2C ','
 {  65,  5, 8,  6,  0, 0 },   // 0x2D '-'
 {  70,  5, 8,  6,  0, 0 },   // 0x2E '.'
 {  75,  5, 8,  6,  0, 0 },   // 0x2F '/'
 {  80,  5, 8,  6,  0, 0 },   // 0x30 '0'
 {  85,  5, 8,  6,  0, 0 },   // 0x31 '1'
 {  90,  5, 8,  6,  0, 0 },   // 0x32 '2'
 {  95,  5, 8,  6,  0, 0 },   // 0x33 '3'
 { 100,  5, 8,  6,  0, 0 },   // 0x34 '4'
 { 105,  5, 8,  6,  0, 0 },   // 0x35 '5'
 { 110,  5, 8,  6,  0, 0 },   // 0x36 '6'
 { 115,  5, 8,  6,  0, 0 },   // 0x37 '7'
 { 120,  5, 8,  6,  0, 0 },   // 0x38 '8'
 { 125,  5, 8,  6,  0, 0 },   // 0x39 '9'
 { 130,  5, 8,  6,  0, 0 },   // 0x3A ':'
 { 135,  5, 8,  6,  0, 0 },   // 0x3B ';'
 { 140,  5, 8,  6,  0, 0 },   // 0x3C '<'
 { 145,  5, 8,  6,  0, 0 },   // 0x3D '='
 { 150,  5, 8,  6,  0, 0 },   // 0x3E '>'
 { 155,  5, 8,  6,  0, 0 },   // 0x3F '?'
 { 160,  5, 8,  6,  0, 0 },   // 0x40 '@'
 { 165,  5, 8,  6,  0, 0 },   // 0x41 'A'
 { 170,  5, 8,  6,  0, 0 },   // 0x42 'B'
 { 175,  5, 8,  6,  0, 0 },   // 0x43 'C'
 { 180,  5, 8,  6,  0, 0 },   // 0x44 'D'
 { 185,  5, 8,  6,  0, 0 },   // 0x45 'E'
 { 190,  5, 8,  6,  0, 0 },   // 0x46 'F'
 { 195,  5, 8,  6,  0, 0 },   // 0x47 'G'
 { 200,  5, 8,  6,  0, 0 },   // 0x48 'H'
 { 205,  5, 8,  6,  0, 0 },   // 0x49 'I'
 { 210,  5, 8,  6,  0, 0 },   // 0x4A 'J'
 { 215,  5, 8,  6,  0, 0 },   // 0x4B 'K'
 { 220,  5, 8,  6,  0, 0 },   // 0x4C 'L'
 { 225,  5, 8,  6,  0, 0 },   // 0x4D 'M'
 { 230,  5, 8,  6,  0, 0 },   // 0x4E 'N'
 { 235,  5, 8,  6,  0, 0 },   // 0x4F 'O'
 { 240,  5, 8,  6,  0, 0 },   // 0x50 'P'
 { 245,  5, 8,  6,  0, 0 },   // 0x51 'Q'
 { 250,  5, 8,  6,  0, 0 },   // 0x52 'R'
 { 255,  5, 8,  6,  0, 0 },   // 0x53 'S'
 { 260,  5, 8,  6,  0, 0 },   // 0x54 'T'
 { 265,  5, 8,  6,  0, 0 },   // 0x55 'U'
 { 270,  5, 8,  6,  0, 0 },   // 0x56 'V'
 { 275,  5, 8,  6,  0, 0 },   // 0x57 'W'
 { 280,  5, 8,  6,  0, 0 },   // 0x58 'X'
 { 285,  5, 8,  6,  0, 0 },   // 0x59 'Y'
 { 290,  5, 8,  6,  0, 0 },   // 0x5A 'Z'
 { 295,  5, 8,  6,  0, 0 },   // 0x5B '['
 { 300,  5, 8,  6,  0, 0 },   // 0x5C '\'
 { 305,  5, 8,  6,  0, 0 },   // 0x5D ']'
 { 310,  5, 8,  6,  0, 0 },   // 0x5E '^'
 { 315,  5, 8,  6,  0, 0 },   // 0x5F '_'
 { 320,  5, 8,  6,  0, 0 },   // 0x60 '`'
 { 325,  5, 8,  6,  0, 0 },   // 0x61 'a'
 { 330,  5, 8,  6,  0, 0 },   // 0x62 'b'
 { 335,  5, 8,  6,  0, 0 },   // 0x63 'c'
 { 340,  5, 8,  6,  0, 0 },   // 0x64 'd'
 { 345,  5, 8,  6,  0, 0 },   // 0x65 'e'
 { 350,  5, 8,  6,  0, 0 },   // 0x66 'f'
 { 355,  5, 8,  6,  0, 0 },   // 0x67 'g'
 { 360,  5, 8,  6,  0, 0 },   // 0x68 'h'
 { 365,  5, 8,  6,  0, 0 },   // 0x69 'i'
 { 370,  5, 8,  6,  0, 0 },   // 0x6A 'j'
 { 375,  5, 8,  6,  0, 0 },   // 0x6B 'k'
 { 380,  5, 8,  6,  0, 0 },   // 0x6C 'l'
 { 385,  5, 8,  6,  0, 0 },   // 0x6D 'm'
 { 390,  5, 8,  6,  0, 0 },   // 0x6E 'n'
 { 395,  5, 8,  6,  0, 0 },   // 0x6F 'o'
 { 400,  5, 8,  6,  0, 0 },   // 0x70 'p'
 { 405,  5, 8,  6,  0, 0 },   // 0x71 'q'
 { 410,  5, 8,  6,  0, 0 },   // 0x72 'r'
 { 415,  5, 8,  6,  0, 0 },   // 0x73 's'
 { 420,  5, 8,  6,  0, 0 },   // 0x74 't'
 { 425,  5, 8,  6,  0, 0 },   // 0x75 'u'
 { 430,  5, 8,  6,  0, 0 },   // 0x76 'v'
 { 435,  5, 8,  6,  0, 0 },   // 0x77 'w'
 { 440,  5, 8,  6,  0, 0 },   // 0x78 'x'
 { 445,  5, 8,  6,  0, 0 },   // 0x79 'y'
 { 450,  5, 8,  6,  0, 0 },   // 0x7A 'z'
 { 455,  5, 8,  6,  0, 0 },   // 0x7B '{'
 { 460,  5, 8,  6,  0, 0 },   // 0x7C '|'
 { 465,  5, 8,  6,  0, 0 },   // 0x7D '}'
 { 470,  5, 8,  6,  0, 0 },   // 0x7E '~'
 { 475,  5, 8,  6,  0, 0 },   // 0x7F '' 
 { 480,  5, 8,  6,  0, 0 },   // 0x80 '�' 
 { 485,  5, 8,  6,  0, 0 },   // 0x81 '�' 
 { 490,  5, 8,  6,  0, 0 },   // 0x82 '�' 
 { 495,  5, 8,  6,  0, 0 },   // 0x83 '�' 
 { 500,  5, 8,  6,  0, 0 },   // 0x84 '�' 
 { 505,  5, 8,  6,  0, 0 },   // 0x85 '�' 
 { 510,  5, 8,  6,  0, 0 },   // 0x86 '�' 
 { 515,  5, 8,  6,  0, 0 },   // 0x87 '�' 
 { 520,  5, 8,  6,  0, 0 },   // 0x88 '�' 
 { 525,  5, 8,  6,  0, 0 },   // 0x89 '�' 
 { 530,  5, 8,  6,  0, 0 },   // 0x8A '�' 
 { 535,  5, 8,  6,  0, 0 },   // 0x8B '�' 
 { 540,  5, 8,  6,  0, 0 },   // 0x8C '�' 
 { 545,  5, 8,  6,  0, 0 },   // 0x8D '�' 
 { 550,  5, 8,  6,  0, 0 },   // 0x8E '�' 
 { 555,  5, 8,  6,  0, 0 },   // 0x8F '�' 
 { 560,  5, 8,  6,  0, 0 },   // 0x90 '�' 
 { 565,  5, 8,  6,  0, 0 },   // 0x91 '�' 
 { 570,  5, 8,  6,  0, 0 },   // 0x92 '�' 
 { 575,  5, 8,  6,  0, 0 },   // 0x93 '�' 
 { 580,  5, 8,  6,  0, 0 },   // 0x94 '�' 
 { 585,  5, 8,  6,  0, 0 },   // 0x95 '�' 
 { 590,  5, 8,  6,  0, 0 },   // 0x96 '�' 
 { 595,  5, 8,  6,  0, 0 },   // 0x97 '�' 
 { 600,  5, 8,  6,  0, 0 },   // 0x98 '�' 
 { 605,  5, 8,  6,  0, 0 },   // 0x99 '�' 
 { 610,  5, 8,  6,  0, 0 },   // 0x9A '�' 
 { 615,  5, 8,  6,  0, 0 },   // 0x9B '�' 
 { 620,  5, 8,  6,  0, 0 },   // 0x9C '�' 
 { 625,  5, 8,  6,  0, 0 },   // 0x9D '�' 
 { 630,  5, 8,  6,  0, 0 },   // 0x9E '�' 
 { 635,  5, 8,  6,  0, 0 },   // 0x9F '�' 
 { 640,  5, 8,  6,  0, 0 },   // 0xA0 '�' 
 { 645,  5, 8,  6,  0, 0 },   // 0xA1 '�' 
 { 650,  5, 8,  6,  0, 0 },   // 0xA2 '�' 
 { 655,  5, 8,  6,  0, 0 },   // 0xA3 '�' 
 { 660,  5, 8,  6,  0, 0 },   // 0xA4 '�' 
 { 665,  5, 8,  6,  0, 0 },   // 0xA5 '�' 
 { 670,  5, 8,  6,  0, 0 },   // 0xA6 '�' 
 { 675,  5, 8,  6,  0, 0 },   // 0xA7 '�' 
 { 680,  5, 8,  6,  0, 0 },   // 0xA8 '�' 
 { 685,  5, 8,  6,  0, 0 },   // 0xA9 '�' 
 { 690,  5, 8,  6,  0, 0 },   // 0xAA '�' 
 { 695,  5, 8,  6,  0, 0 },   // 0xAB '�' 
 { 700,  5, 8,  6,  0, 0 },   // 0xAC '�' 
 { 705,  5, 8,  6,  0, 0 },   // 0xAD '�' 
 { 710,  5, 8,  6,  0, 0 },   // 0xAE '�' 
 { 715,  5, 8,  6,  0, 0 },   // 0xAF '�' 
 { 720,  5, 8,  6,  0, 0 },   // 0xB0 '�' 
 { 725,  5, 8,  6,  0, 0 },   // 0xB1 '�' 
 { 730,  5, 8,  6,  0, 0 },   // 0xB2 '�' 
 { 735,  5, 8,  6,  0, 0 },   // 0xB3 '�' 
 { 740,  5, 8,  6,  0, 0 },   // 0xB4 '�' 
 { 745,  5, 8,  6,  0, 0 },   // 0xB5 '�' 
 { 750,  5, 8,  6,  0, 0 },   // 0xB6 '�' 
 { 755,  5, 8,  6,  0, 0 },   // 0xB7 '�' 
 { 760,  5, 8,  6,  0, 0 },   // 0xB8 '�' 
 { 765,  5, 8,  6,  0, 0 },   // 0xB9 '�' 
 { 770,  5, 8,  6,  0, 0 },   // 0xBA '�' 
 { 775,  5, 8,  6,  0, 0 },   // 0xBB '�' 
 { 780,  5, 8,  6,  0, 0 },   // 0xBC '�' 
 { 785,  5, 8,  6,  0, 0 },   // 0xBD '�' 
 { 790,  5, 8,  6,  0, 0 },   // 0xBE '�' 
 { 795,  5, 8,  6,  0, 0 },   // 0xBF '�' 
 { 800,  5, 8,  6,  0, 0 },   // 0xC0 '�' 
 { 805,  5, 8,  6,  0, 0 },   // 0xC1 '�' 
 { 810,  5, 8,  6,  0, 0 },   // 0xC2 '�' 
 { 815,  5, 8,  6,  0, 0 },   // 0xC3 '�' 
 { 820,  5, 8,  6,  0, 0 },   // 0xC4 '�' 
 { 825,  5, 8,  6,  0, 0 },   // 0xC5 '�' 
 { 830,  5, 8,  6,  0, 0 },   // 0xC6 '�' 
 { 835,  5, 8,  6,  0, 0 },   // 0xC7 '�' 
 { 840,  5, 8,  6,  0, 0 },   // 0xC8 '�' 
 { 845,  5, 8,  6,  0, 0 },   // 0xC9 '�' 
 { 850,  5, 8,  6,  0, 0 },   // 0xCA '�' 
 { 855,  5, 8,  6,  0, 0 },   // 0xCB '�' 
 { 860,  5, 8,  6,  0, 0 },   // 0xCC '�' 
 { 865,  5, 8,  6,  0, 0 },   // 0xCD '�' 
 { 870,  5, 8,  6,  0, 0 },   // 0xCE '�' 
 { 875,  5, 8,  6,  0, 0 },   // 0xCF '�' 
 { 880,  5, 8,  6,  0, 0 },   // 0xD0 '�' 
 { 885,  5, 8,  6,  0, 0 },   // 0xD1 '�' 
 { 890,  5, 8,  6,  0, 0 },   // 0xD2 '�' 
 { 895,  5, 8,  6,  0, 0 },   // 0xD3 '�' 
 { 900,  5, 8,  6,  0, 0 },   // 0xD4 '�' 
 { 905,  5, 8,  6,  0, 0 },   // 0xD5 '�' 
 { 910,  5, 8,  6,  0, 0 },   // 0xD6 '�' 
 { 915,  5, 8,  6,  0, 0 },   // 0xD7 '�' 
 { 920,  5, 8,  6,  0, 0 },   // 0xD8 '�' 
 { 925,  5, 8,  6,  0, 0 },   // 0xD9 '�' 
 { 930,  5, 8,  6,  0, 0 },   // 0xDA '�' 
 { 935,  5, 8,  6,  0, 0 },   // 0xDB '�' 
 { 940,  5, 8,  6,  0, 0 },   // 0xDC '�' 
 { 945,  5, 8,  6,  0, 0 },   // 0xDD '�' 
 { 950,  5, 8,  6,  0, 0 },   // 0xDE '�' 
 { 955,  5, 8,  6,  0, 0 },   // 0xDF '�' 
 { 960,  5, 8,  6,  0, 0 },   // 0xE0 '�' 
 { 965,  5, 8,  6,  0, 0 },   // 0xE1 '�' 
 { 970,  5, 8,  6,  0, 0 },   // 0xE2 '�' 
 { 975,  5, 8,  6,  0, 0 },   // 0xE3 '�' 
 { 980,  5, 8,  6,  0, 0 },   // 0xE4 '�' 
 { 985,  5, 8,  6,  0, 0 },   // 0xE5 '�' 
 { 990,  5, 8,  6,  0, 0 },   // 0xE6 '�' 
 { 995,  5, 8,  6,  0, 0 },   // 0xE7 '�' 
 {1000,  5, 8,  6,  0, 0 },   // 0xE8 '�' 
 {1005,  5, 8,  6,  0, 0 },   // 0xE9 '�' 
 {1010,  5, 8,  6,  0, 0 },   // 0xEA '�' 
 {1015,  5, 8,  6,  0, 0 },   // 0xEB '�' 
 {1020,  5, 8,  6,  0, 0 },   // 0xEC '�' 
 {1025,  5, 8,  6,  0, 0 },   // 0xED '�' 
 {1030,  5, 8,  6,  0, 0 },   // 0xEE '�' 
 {1035,  5, 8,  6,  0, 0 },   // 0xEF '�' 
 {1040,  5, 8,  6,  0, 0 },   // 0xF0 '�' 
 {1045,  5, 8,  6,  0, 0 },   // 0xF1 '�' 
 {1050,  5, 8,  6,  0, 0 },   // 0xF2 '�' 
 {1055,  5, 8,  6,  0, 0 },   // 0xF3 '�' 
 {1060,  5, 8,  6,  0, 0 },   // 0xF4 '�' 
 {1065,  5, 8,  6,  0, 0 },   // 0xF5 '�' 
 {1070,  5, 8,  6,  0, 0 },   // 0xF6 '�' 
 {1075,  5, 8,  6,  0, 0 },   // 0xF7 '�' 
 {1080,  5, 8,  6,  0, 0 },   // 0xF8 '�' 
 {1085,  5, 8,  6,  0, 0 },   // 0xF9 '�' 
 {1090,  5, 8,  6,  0, 0 },   // 0xFA '�' 
 {1095,  5, 8,  6,  0, 0 },   // 0xFB '�' 
 {1100,  5, 8,  6,  0, 0 },   // 0xFC '�' 
 {1105,  5, 8,  6,  0, 0 },   // 0xFD '�' 
 {1110,  5, 8,  6,  0, 0 },   // 0xFE '�' 
 {1115,  5, 8,  6,  0, 0 } }; // 0xFF '�' 

const GFXfont fontKH_5x8 PROGMEM = {
  (uint8_t  *)fontKH_5x8Bitmaps,
  (GFXglyph *)fontKH_5x8Glyphs,
  0x20, 0xFF, 8};

#endif
