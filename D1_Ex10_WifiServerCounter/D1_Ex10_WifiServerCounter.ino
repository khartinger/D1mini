//_____D1_Ex10_WifiServerCounter___________________20160727_____
// Server listens to Port 80 and counts the requests.
// Blue LED on shows a incoming request.
// HTTP-Answer: number of request
// Serial: client ip and number of request (57600 baud)
// The website and all server functions a placed in header file
//   D1_Ex10_WifiServerCounter.h
// Hardware: WeMos D1 mini
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
const int pinLED=D4;
int requestCounter=0;
#include "D1_Ex10_WifiServerCounter.h"

//_____setup routine____________________________________________
void setup(void){
 Serial.begin(57600);
 pinMode(pinLED, OUTPUT);
 digitalWrite(pinLED, 1);        // LED off
 setup_webserver();
}

//_____main loop________________________________________________
void loop(void){
 server.handleClient();
}
