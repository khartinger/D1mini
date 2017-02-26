//_____D1_Ex30_WifiAPCounterIntD5OledConf.ino______20170226_____
// Accesspoint 192.168.1.111 listens to Port 80 and increments
// counter on request or increments counter on falling edge D5.
// + Push the Button D5 more then 3 sec resets counter
// + browser request 192.168.1.111/resetcounter resets counter
// + blue led indicates a http-request
// HTTP-Answer   : counter value
// OLED-Display  : counter value, client ip and signal strength
// Serial monitor: config mode, log messages (19200Bd)
// Config-Mode   : connect TX and RX while reset (3s -> reset)
// Serial monitor: config mode, log messages (19200Bd)
// All websites, server, oled and interrupt functions a placed in file
//   D1_ConfigServerEEprom.h
//   D1_Ex30_WifiAPCounterIntD5OledConf.h

// Hardware: WeMos D1 Mini
//           Push Button at D5
//           OLED Shield: SSD1306, 64x48 pixel, I2C
//                        SCL GPIO5, SDA GPIO4, OLED_RESET GPIO0
// Uses Adafruit libs Adafruit_SSD1306-esp8266-64x48.zip and
//                    Adafruit-GFX-Library-1.1.5.zip
extern "C" {
#include "user_interface.h"
}
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include "fonts/font2_5x8.h"
#define PIN_LED     D4                 // D4=GPIO2
#define PIN_BUTTON  D5                 // D5=GPIO14
#define OLED_RESET  D3                 // D3=GPIO0
Adafruit_SSD1306 display(OLED_RESET);

#include "D1_Ex30_WifiAPCounterIntD5OledConf.h"
#include "D1_ConfigServerEeprom.h"

//_____setup routine____________________________________________
void setup(void){
 Serial.begin(19200);
 pinMode(PIN_BUTTON, INPUT);
 attachInterrupt(PIN_BUTTON, io_interrupt, CHANGE);
 pinMode(PIN_LED, OUTPUT);
 digitalWrite(PIN_LED, 1);                   // LED off
 display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // I2C addr 0x3C
 display.setTextColor(WHITE);
 //display.setFont(NULL);
 display.setFont(&font2_5x8);
 setup_config_server();
 setup_softAP();                  // calls setup_webserver()
}

//_____main loop________________________________________________
void loop(void){
 server.handleClient();
}
