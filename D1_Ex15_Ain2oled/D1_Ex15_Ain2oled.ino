//_____D1_Ex15_Ain2oled.ino________________________20160802_____
// Display Analog In on OLED Shield
// and calculate input to another range (3..996 -> 0..255)
// Hardware:
// * WeMos D1 Mini
// * trimmer (poti) at pins GND-A0-3V3
// * OLED Shield: SSD1306, 64x48 pixel, I2C
//   (SCL=D1=GPIO5, SDA=D2=GPIO4, OLED_RESET=D3=GPIO0)
// Uses Adafruit libs Adafruit_SSD1306-esp8266-64x48.zip and
//                    Adafruit-GFX-Library-1.1.5.zip
//include <SPI.h>
//#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

const int pinAin=A0;
#define OLED_RESET 0              // OLED_RESET=D3=GPIO0
Adafruit_SSD1306 display(OLED_RESET);

//_____show value and client ip on oled-display_________
void display_oled(String sCounter, String sLine56)
{
 int x=32-6*sCounter.length();
 display.clearDisplay();          // Clear the display-buffer
 display.drawRect(0,0,63,29,WHITE);
 display.setTextSize(2);
 display.setCursor(x,8);
 display.println(sCounter);
 display.setTextSize(1);
 display.setCursor(0,33);
 display.println(sLine56);
 display.display();               // show buffer
}

void setup() {
 Serial.begin(9600);
 pinMode(pinAin, OUTPUT);
 display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // I2C addr 0x3C
 display.setTextColor(WHITE);
 display.clearDisplay();          // Clear the display-buffer
}

void loop() {
 char temp_[10];
 //-----value should be 0...1023, real value 3..996------
 int sensorValue = analogRead(pinAin);
 String sSensorValue=String(sensorValue); 
 sSensorValue="--Sensor-- "+sSensorValue;
 //-----calculate sensor value (3..996) to 0..255--------
 float val=(255.0*(sensorValue-5)/989);
 if(val<0) val=0;
 if(val>255) val=255;
 dtostrf(val,3,0,temp_);     // format float 3.0
 String sValueNew=String(temp_);
 //-----display both values------------------------------
 display_oled(sValueNew,sSensorValue);
}
