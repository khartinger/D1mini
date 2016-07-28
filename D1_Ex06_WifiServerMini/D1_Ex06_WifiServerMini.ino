//_____D1_Ex06_WifiServerMini______________________20160727_____
// Server listens to Port 80 and answers to
// (1) request without uri: Message Hello from D1Mini
// You can set the ip-address or use dhcp
// DON´T FORGET TO CHANGE *ssid AND *password !
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

const char *ssid = "*****";
const char *password = "*****";
IPAddress ip(192,168,0,123);
IPAddress gateway(192,168,0,1);
IPAddress subnet(255,255,255,0);

ESP8266WebServer server(80);

//_____send answer (request without uri or argument)____________
void handleRoot() {
  server.send(200, "text/plain", "Hello from eps8266 WifiServer Mini!");
  Serial.println("Request without Parameters (root)!");
}

//_____setup routine____________________________________________
void setup(void){
 Serial.begin(9600);
 Serial.println("");
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
 Serial.print("IP address: ");
 Serial.println(WiFi.localIP());
 //-----start mDNS----------------------------------------------
 if (MDNS.begin("esp8266")) {
  Serial.println("MDNS responder started");
 }
 //-----handles to answer the request---------------------------
 server.on("/", handleRoot);
 //-----start server--------------------------------------------
 server.begin();
 Serial.println("HTTP server started");
}

//_____main loop________________________________________________
void loop(void){
 server.handleClient();
}
