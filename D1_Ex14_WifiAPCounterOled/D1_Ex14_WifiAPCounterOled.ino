//_____D1_Ex14_WifiAPCounterOled___________________20160728_____
// Accesspoint listens to Port 80 and counts the requests.
// HTTP-Answer: number of request
// OLED-Display: number of request and client ip
// All server functions a placed in header file
//   D1_Ex14_WifiAPCounterOled.h
// Hardware: WeMos D1 Mini
//           OLED Shield: SSD1306, 64x48 pixel, I2C
//                        SCL GPIO5, SDA GPIO4, OLED_RESET GPIO0
// Uses Adafruit libs Adafruit_SSD1306-esp8266-64x48.zip and
//                    Adafruit-GFX-Library-1.1.5.zip
#include <ESP8266WiFi.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
const int pinLED=D4;
#include "D1_Ex14_WifiAPCounterOled.h"

//_____setup routine____________________________________________
void setup(void){
 Serial.begin(115200);
 pinMode(pinLED, OUTPUT);
 digitalWrite(pinLED, 1);                    // LED off
 display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // I2C addr 0x3C
 display.setTextColor(WHITE);
 setup_accesspoint();
}

//_____main loop________________________________________________
void loop(void){
 handleClient();
}
