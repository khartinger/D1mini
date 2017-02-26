//_____D1_Ex29_WifiServerLedConfig.ino________170222-170226_____
// Server listens to Port 80 and answers to
// (1) request /?led=on or /?led=0ff switches blue LED (D4=GPIO2)
//     on or off
// (2) request /config
//     shows input website for WiFi parameters
// (3) for config/reset: connect TX-RX while system start
// (4) all other requests : error message
// The website and all server functions a placed in header file
//   D1_Ex29_WifiServerLedConfig.h
//   D1_ConfigServerEEprom.h
// Addresses from/to EEPROM or default
// Hardware: Webos D1 mini

#define PIN_LED D4
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include "D1_Ex29_WifiServerLedConfig.h"
#include "D1_ConfigServerEeprom.h"

//_____setup routine____________________________________________
void setup(void){
 Serial.begin(19200);
 pinMode(PIN_LED, OUTPUT);
 setup_config_server();
 setup_webserver();
}

//_____main loop________________________________________________
void loop(void){
 //-----Handle requests-----------------------------------------
 server.handleClient();
}
