//_____D1_Ex08_WifiServerUri.h_____________________20160727_____
// Server listens to Port 80 and answers to
// (1) request without uri: HTML-Website showing the clientIP
// (2) request /set like /set?x=3: count & show params x: 3 etc.
// (3) all other requests : error message
// The website and all server functions a placed in header file
// D1_Ex08_WifiServerUri.h

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include "D1_Ex08_WifiServerUri.h"

int counter_ms=0;
int counter_s=0;
//_____setup routine____________________________________________
void setup(void){
 Serial.begin(9600);
 setup_webserver();
}

//_____main loop________________________________________________
void loop(void){
 //-----counter to show working on Serial-----------------------
 counter_ms++;
 if(counter_ms>1000) { 
  counter_ms=0;
  counter_s++;
  if(counter_s>3600) counter_s=0;
  Serial.print("Zaehler="); 
  Serial.println(counter_s); 
 }
 delay(1);
 //-----Handle requests-----------------------------------------
 server.handleClient();
}
