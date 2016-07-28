//_____D1_ex07_HelloWebsite.h______________________20160727_____
#ifndef D1_EX07_HELLOWEBSITE_H
#define D1_EX07_HELLOWEBSITE_H
#include "myWifiData.h"  // contains private *ssid and *password
//const char *ssid = "*****";
//const char *password = "*****";
IPAddress ip(192,168,0,123);
IPAddress gateway(192,168,0,1);
IPAddress subnet(255,255,255,0);

ESP8266WebServer server(80);

//_____returns string with html code of website_________________
String htmlcode(String s2)
{
 String s1="";
 s1+="<html><head><title>HelloWebsite</title></head>\n<body>\n";
 s1+="<h1>Hello!</h1>Welcome "+s2+" to D1mini Website :)";
 s1+="\n</body></html>";
 return s1;
}

//_____send answer (request without uri or argument)____________
void handleRoot() {
 WiFiClient client = server.client();
 IPAddress ipc=client.remoteIP();
 String sIPc=ipc.toString();
 Serial.println("Request "+sIPc+"!");
 server.send(200, "text/html", htmlcode(sIPc));
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
 Serial.println("-----Setup webserver-----");
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
 server.onNotFound(handleNotFound);
 //-----start server--------------------------------------------
 server.begin();
 Serial.println("HTTP server started");
}
#endif
