//_____D1_Ex07_HelloWebsite________________________20160727_____
// Server listens to Port 80 and answers to
// (1) request without uri: HTML-Website showing the clientIP
// (2) all other requests : error message
// The website and all server functions a placed in header file
// D1_Ex07_HelloWebsite.h
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include "D1_Ex07_HelloWebsite.h"

//_____setup routine____________________________________________
void setup(void){
 Serial.begin(9600);
 setup_webserver();
}

//_____main loop________________________________________________
void loop(void){
 server.handleClient();
}
