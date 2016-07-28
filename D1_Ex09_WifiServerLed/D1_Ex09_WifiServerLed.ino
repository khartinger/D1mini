//_____D1_Ex09_WifiServerLed.h_____________________20160727_____
// Server listens to Port 80 and answers to
// (1) request /?led=on or /?led=0ff switches blue LED (D4=GPIO2)
//     on or off
// (2) all other requests : error message
// The website and all server functions a placed in header file
// D1_Ex09_WifiServerLed.h
// Hardware: Webos D1 mini

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
const int pinLED=D4;
#include "D1_Ex09_WifiServerLed.h"

//_____setup routine____________________________________________
void setup(void){
 Serial.begin(9600);
 pinMode(pinLED, OUTPUT);
 setup_webserver();
}

//_____main loop________________________________________________
void loop(void){
 //-----Handle requests-----------------------------------------
 server.handleClient();
}
