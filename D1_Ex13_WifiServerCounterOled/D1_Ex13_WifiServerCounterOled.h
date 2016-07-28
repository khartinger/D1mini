//_____D1_Ex13_WifiServerCounterOled.h_____________20160728_____
#ifndef D1_EX13_WIFISERVERCOUNTEROLED_H
#define D1_EX13_WIFISERVERCOUNTEROLED_H
#include "myWifiData.h"  // contains private *ssid and *password
//const char *ssid = "*****";
//const char *password = "*****";
IPAddress ip(192,168,0,123);
IPAddress gateway(192,168,0,1);
IPAddress subnet(255,255,255,0);
#define OLED_RESET 0                   // OLED_RESET=D3=GPIO0
Adafruit_SSD1306 display(OLED_RESET);
int requestCounter=0;
ESP8266WebServer server(80);

//_____show counter value and client ip on oled-display_________
void display_oled(String sCounter, String sLine56)
{
 int x=32-6*sCounter.length();
 display.clearDisplay();          // Clear the display-buffer
 display.drawRect(0,0,63,29,WHITE);
 display.setTextSize(2);
 display.setCursor(x,8);
 display.println(sCounter);
 display.setTextSize(1);
 display.setCursor(0,33);
 display.println(sLine56);
 display.display();               // show buffer
}

//_____returns line with client ip and signal strength__________
String getLine56()
{
 WiFiClient client = server.client();
 IPAddress ipc=client.remoteIP();
 String sIPc = ipc.toString();
 String sRssi = String(WiFi.RSSI());
 String sLine56 = sIPc + " " + sRssi+"dBm";
 return sLine56;
}

//_____send answer (request without uri or argument)____________
void handleRoot() {
 requestCounter++;
 String sCounter = String(requestCounter);
 String sLine56 = getLine56();
 display_oled(sCounter, sLine56);
 String s1=sCounter + " | OK. Client: " + sLine56;
 Serial.println(s1);
 server.send(200, "text/plain", s1);
}

//_____send answer if file (uri) not found______________________
void handleNotFound(){
 requestCounter++;
 String sCounter = String(requestCounter);
 String sLine56 = getLine56();
 display_oled(sCounter, sLine56);
 String s1=sCounter + " | File not found. Client: " + sLine56;
 Serial.println(s1);
 server.send(404, "text/plain", s1);
}

//_____start the webserver______________________________________
void setup_webserver()
{
 Serial.println("\n-----Setup webserver-----");
 WiFi.begin(ssid, password);
 WiFi.config(ip, gateway, subnet);  // skipp for dhcp
 //-----Wait for connection-------------------------------------
 while (WiFi.status() != WL_CONNECTED) {
  delay(500);
  Serial.print(".");
 }
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
 //-----init oled display---------------------------------------
 display_oled("0", "Server "+ip.toString());
}
#endif
