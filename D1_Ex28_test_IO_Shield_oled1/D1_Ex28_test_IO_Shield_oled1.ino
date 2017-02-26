//_____D1_Ex28_test_IO_Shield_oled1.ino_______170202-170206_____
// Function: Red LED lights up for 1,5s, green LED 0,5s, ...
//           If button is pressed, both LEDs are on
//            (=> yellow, if DUO-LED is used).
// Hardware: (1) WeMos D1 mini
//           (2) D1_IO_Shield1: 2x LEDs at D7 (green), D8 (red)
//                              1x Button at D5
//           (3) OLED Shield: SSD1306, 64x48 pixel, I2C
// Software: (1) Adafruit libs Adafruit_SSD1306-esp8266-64x48.zip
//           (2) Adafruit-GFX-Library-1.1.5.zip
//           (3) Font font2_5x8.h in subdirectory fonts
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include "fonts/font2_5x8.h"
#define OLED_RESET    D3               // D3=GPIO0
#define PIN_BUTTON    D5               // D5=GPIO14
#define PIN_LED_GREEN D7               // D7=GPIO13
#define PIN_LED_RED   D8               // D8=GPIO15
#define STATE_NO      -1               // nothing to do
#define STATE_0        0               // 0...1,4s
#define STATE_1       15               // 1,5...2s
#define STATE_2       20               // back to STATE_0
Adafruit_SSD1306 display(OLED_RESET);
int state=STATE_0, state_restore=STATE_NO;

//_____show counter value and client ip on oled-display_________
void display_oled(int state_led)
{
 display.clearDisplay();               // Clear display-buffer
 display.drawRect(0,0,63,39,WHITE);    // border around display
 display.setCursor(24,2);              //
 display.println("HTL");               //
 display.setCursor(9,10);              //
 display.println("KAINDORF");          //
 display.setCursor(3,40);              //
 display.println("(c) by ht");         //
 display.drawLine(1,18,62,18,WHITE);   //
 //-----text LED green------------------------------------------
 display.setCursor(8,20);              //
 if(state_led&1)
  display.println("LED gr\x81n");      //
 else
  display.println("        ");         //
 //-----text LED red-------------------------------------------- 
 display.setCursor(8,29);              //
 if(state_led&2)
  display.println("LED rot");          //
 else
  display.println("        ");         //
 display.display();                    // show buffer
}

void setup() {
 pinMode(PIN_BUTTON, INPUT);
 pinMode(PIN_LED_GREEN, OUTPUT);
 pinMode(PIN_LED_RED, OUTPUT);
 //-----setup oled display--------------------------------------
 display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // I2C addr 0x3C
 display.setTextColor(WHITE);
 display.setFont(&font2_5x8);
 display.setTextSize(1);
}

void loop() 
{
 int in1_;
 in1_= digitalRead(PIN_BUTTON);
 if(in1_) //=====button not pressed=============================
 { 
  if((state==STATE_0)||(state_restore==STATE_0))
  { //-----red LED lights up------------------------------------
   digitalWrite(PIN_LED_RED, 1);
   digitalWrite(PIN_LED_GREEN, 0);
   display_oled(2);
   state_restore=STATE_NO;
  }
  if((state==STATE_1)||(state_restore==STATE_1))
  { //-----green LED lights up----------------------------------
   digitalWrite(PIN_LED_GREEN, 1);
   digitalWrite(PIN_LED_RED, 0);
   display_oled(1);
   state_restore=STATE_NO;
  }
  state++;
  if(state>STATE_2) { state=STATE_0; state_restore=STATE_NO; }
 }
 else //=====button pressed=====================================
 { 
  //-----state after button released----------------------------
  if(state<STATE_1) state_restore=STATE_0;
  else
  { if(state<STATE_2) state_restore=STATE_1;
    else state_restore=STATE_2;
  }
  //-----both LEDs light up------------------------------------
  digitalWrite(PIN_LED_GREEN, 1);
  digitalWrite(PIN_LED_RED, 1);
  display_oled(3);
 }
 delay(100);
}

