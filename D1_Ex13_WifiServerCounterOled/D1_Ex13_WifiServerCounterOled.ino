//_____D1_Ex13_WifiServerCounterOled_______________20160728_____
// Server listens to Port 80 and counts the requests.
// HTTP-Answer: number of request
// OLED-Display: number of request and client ip
// The website and all server functions a placed in header file
//   D1_Ex13_WifiServerCounterOled.h
// Hardware: WeMos D1 Mini
//           OLED Shield: SSD1306, 64x48 pixel, I2C
//                        SCL GPIO5, SDA GPIO4, OLED_RESET GPIO0
// Uses Adafruit libs Adafruit_SSD1306-esp8266-64x48.zip and
//                    Adafruit-GFX-Library-1.1.5.zip
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include "D1_Ex13_WifiServerCounterOled.h"

//_____setup routine____________________________________________
void setup(void){
 Serial.begin(57600);
 display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // I2C addr 0x3C
 display.setTextColor(WHITE);
 setup_webserver();
}

//_____main loop________________________________________________
void loop(void){
 server.handleClient();
}
