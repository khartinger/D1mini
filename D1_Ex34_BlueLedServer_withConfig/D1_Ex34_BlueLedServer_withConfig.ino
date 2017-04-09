//_____D1_Ex33_BlueLedServer_withConfig.ino___170409-170409_____
// Host listens to Port 80 for request /on or /off to turn
//  blue D1 mini LED on or off
// On boot up blue led is on, when connected to wlan led is off
// Answer to request: plain text OK
// Serial monitor: log messages (9600Bd)
// Hardware: WeMos D1 Mini
#define PIN_LED_BLUE D4

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include "myWLAN.h"
ESP8266WebServer server(80);
#include "D1_configWlanEeprom.h"  // ***for wlan config!***

//_____on http-request: turn blue led on________________________
void handleOn(void)
{
 digitalWrite(PIN_LED_BLUE, 0);   // blue LED on (!)
 server.send(200, "text/plain", "OK");
}

//_____on http-request: turn blue led off_______________________
void handleOff(void)
{
 digitalWrite(PIN_LED_BLUE, 1);   // blue LED off (!)
 server.send(200, "text/plain", "OK");
}

//_____on http-request without parameter________________________
void handleRoot(void)
{
 server.send(200, "text/plain", "Blue led server ready!");
}

//_____setup wlan________________________________________________
void setup_wlan()
{
 int i=50;
 while(i==50)
 {
  WiFi.disconnect();
  delay(200);
  WiFi.config(ip, gateway, subnet);  // skipp for dhcp
  WiFi.begin(ssid_, pass_);
  //.....wait until connected to WLAN (access point)............
  while(WiFi.status()!=WL_CONNECTED)
  {
   delay(200);
   Serial.print(".");
   i--; if(i<1) { i=50; Serial.println(""); }
  }
 }  
}

//_____setup routine____________________________________________
void setup(void){
 //-----start serial interface----------------------------------
 Serial.begin(9600);
 Serial.println("");
 //-----turn blue LED on----------------------------------------
 pinMode(PIN_LED_BLUE, OUTPUT);
 digitalWrite(PIN_LED_BLUE, 0);   // blue LED on (!)
 //-----setup WLAN----------------------------------------------
 setup_config_wlan();             // ***for wlan config!***
 setup_wlan();
 //-----connected - turn blue LED off---------------------------
 digitalWrite(PIN_LED_BLUE, 1);   // blue LED off (!)
 //-----handles to answer the request---------------------------
 server.on("/", handleRoot);
 server.on("/on", handleOn);
 server.on("/off", handleOff);
 //-----start server--------------------------------------------
 server.begin();
 Serial.println("\nHTTP server started");
}

//_____main loop________________________________________________
void loop(void){
 server.handleClient();
}
