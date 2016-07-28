//_____D1_Ex10_WifiServerCounter.h_________________20160727_____
#ifndef D1_EX10_WIFISERVERCOUNTER_H
#define D1_EX10_WIFISERVERCOUNTER_H
#include "myWifiData.h"  // contains private *ssid and *password
//const char *ssid = "*****";
//const char *password = "*****";
IPAddress ip(192,168,0,123);
IPAddress gateway(192,168,0,1);
IPAddress subnet(255,255,255,0);

ESP8266WebServer server(80);

//_____send answer (request without uri or argument)____________
void handleRoot() {
 digitalWrite(pinLED, 0);              // LED on
 requestCounter++;
 WiFiClient client = server.client();
 IPAddress ipc=client.remoteIP();
 String sIPc=ipc.toString();
 int rssi = WiFi.RSSI();
 String s1="Request from "+sIPc;
 s1=s1+", "+String(rssi)+" dBm -> Counter = "+String(requestCounter);
 Serial.println(s1);
 server.send(200, "text/plain", s1);
 digitalWrite(pinLED, 1);              // LED off
}

//_____send answer if file (uri) not found______________________
void handleNotFound(){
 digitalWrite(pinLED, 0);              // LED on
 requestCounter++;
 WiFiClient client = server.client();
 IPAddress ipc=client.remoteIP();
 String sIPc=ipc.toString();
 String s1 = "Request from "+sIPc+" -> File Not Found. ";
 s1 = s1 + "Counter = "+String(requestCounter);
 Serial.println(s1);
 server.send(404, "text/plain", s1);
 digitalWrite(pinLED, 1);              // LED off
}

//_____start the webserver______________________________________
void setup_webserver()
{
 Serial.println("\n-----Setup webserver-----");
 WiFi.config(ip, gateway, subnet);  // skipp for dhcp
 WiFi.begin(ssid, password);
  //-----Wait for connection-------------------------------------
 while (WiFi.status() != WL_CONNECTED) {
  delay(500);
  Serial.print(".");
 }
 //-----send connection info to serial interface----------------
 Serial.println("");
 Serial.print("Connected to ");
 Serial.println(ssid);
 Serial.print("Signal strength: ");
 int rssi = WiFi.RSSI();
 Serial.print(rssi);
 Serial.println(" dBm");
 Serial.print("Server IP address: ");
 Serial.println(WiFi.localIP());
 //-----start mDNS----------------------------------------------
 if (MDNS.begin("esp8266")) {
  Serial.println("MDNS responder started");
 }
 //-----handles to answer the request---------------------------
 server.on("/", handleRoot);
 server.onNotFound(handleNotFound);
 //-----start server--------------------------------------------
 server.begin();
 Serial.println("HTTP server started");
}
#endif
