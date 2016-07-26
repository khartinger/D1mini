//_____D1_Ex05_text2oled1.ino______________________20160726_____
// Display text on OLED shield (10 characters, 6 lines)
// Hardware: WeMos D1 Mini
//           OLED Shield: SSD1306, 64x48 pixel, I2C
//                        SCL GPIO5, SDA GPIO4, OLED_RESET GPIO0
// Uses Adafruit libs Adafruit_SSD1306-esp8266-64x48.zip and
//                    Adafruit-GFX-Library-1.1.5.zip
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

// default pins: SCL=D1=GPIO5, SDA=D2=GPIO4
#define OLED_RESET 0  // GPIO0
Adafruit_SSD1306 display(OLED_RESET);

void setup()   {
 Serial.begin(9600);
 display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // I2C addr 0x3C
 display.setTextColor(WHITE);
 display.clearDisplay();          // Clear the display-buffer
 //-----write text to buffer------------------------------------
 display.setTextSize(1);
 display.setCursor(0,0);
 display.println("1234567890");
 display.println("abcdefghij");
 display.println("ABCDEFGHIJ");
 display.println("--Line 4--");
 display.println("1234567890");
 display.println("-_Line 6_-");
 display.display();               // show buffer
}

void loop() {
}
