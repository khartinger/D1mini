//_____D1_Ex08_WifiServerUri.h_____________________20160727_____
#ifndef D1_EX08_WIFISERVERURI_H
#define D1_EX08_WIFISERVERURI_H
#include "myWifiData.h"  // contains private *ssid and *password
//const char *ssid = "*****";
//const char *password = "*****";
IPAddress ip(192,168,0,123);
IPAddress gateway(192,168,0,1);
IPAddress subnet(255,255,255,0);

ESP8266WebServer server(80);

//_____send answer (request without uri or argument)____________
void handleRoot() {
 String sIPc=server.client().remoteIP().toString();
 String s1="Hello "+sIPc+"!\nYou are conneted to "+ip.toString()+".\n";
 s1+="Use /set?name=value&.. to show parameters.";
 server.send(200, "text/plain", s1);
 Serial.println("Request from "+sIPc+"!");
}

//_____send answer to set-Request_______________________________
void handleSet() {
 String s="Set-Anfrage mit ";
 s += server.args();
 s += " Parameter(n):\n";
 for (uint8_t i=0; i<server.args(); i++)
  s += " " + server.argName(i) + ": " + server.arg(i) + "\n";
 server.send(200, "text/plain", s);
 Serial.println("set-Request: "+s);
}

//_____send answer if file (uri) not found______________________
void handleNotFound(){
 String s = "File Not Found\n";
 s += "URI: " + server.uri();
 server.send(404, "text/plain", s);
 Serial.println("Request: "+s);
}

//_____start the webserver______________________________________
void setup_webserver()
{
 WiFi.begin(ssid, password);
 WiFi.config(ip, gateway, subnet);  // skipp for dhcp
 //-----Wait for connection-------------------------------------
 while (WiFi.status() != WL_CONNECTED) {
  delay(500);
  Serial.print(".");
 }
 //-----send connection info to serial interface----------------
 Serial.println("");
 Serial.print("Connected to ");
 Serial.println(ssid);
 Serial.print("Server IP address: ");
 Serial.println(WiFi.localIP());
 //-----start mDNS----------------------------------------------
 if (MDNS.begin("esp8266")) {
  Serial.println("MDNS responder started");
 }
 //-----handles to answer the request---------------------------
 server.on("/", handleRoot);
 server.on("/set", handleSet);
 server.onNotFound(handleNotFound);
 //-----start server--------------------------------------------
 server.begin();
 Serial.println("HTTP server started");
}

#endif
