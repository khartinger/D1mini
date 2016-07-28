//_____D1_Ex12_WifiClientButton.h__________________20160727_____
#ifndef D1_EX12_WIFICLIENTBUTTON_H
#define D1_EX12_WIFICLIENTBUTTON_H
#include "myWifiData.h"  // contains private *ssid and *password
//const char *ssid = "*****";
//const char *password = "*****";
IPAddress ip(192,168,0,101);
IPAddress gateway(192,168,0,1);
IPAddress subnet(255,255,255,0);
char* host = "192.168.0.123";    // or "http://..."
int httpPort=80;
WiFiClient client;

//_____start the webserver______________________________________
void setup_webclient()
{
 Serial.println("\n-----Setup wifi connection-----");
 WiFi.mode(WIFI_STA);
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
 Serial.print("Client IP address: ");
 Serial.println(WiFi.localIP());
}

//_____send a request and show response at Serial---------------
void loop_webclient(String uri)
{
 if (!client.connect(host, httpPort)) {
  Serial.println("ERROR: connection failed!");
 }
 else
 {
  //-----connected, send request--------------------------------
  digitalWrite(pinLED, 0);       // LED on
  Serial.println("\nConnected to " + String(host));
  Serial.print("Signal strength: ");
  int rssi = WiFi.RSSI();
  Serial.print(rssi);
  Serial.println(" dBm");
  String request="GET "+ uri +  " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" + 
                 "Connection: close\r\n\r\n";
  client.print(request);
  delay(10);
  Serial.println("-----Response:-------------");
/* 
  //-----quick check of response--------------------------------
  if(client.available()) Serial.println("OK");              // |
                    else Serial.println("ERROR");           // |
*/
  //-----slow: read all lines of server reply, print to Serial---
  String line="";
  while(client.available()){
   line = client.readStringUntil('\r');
   Serial.print(line);
  }
  Serial.println();
  Serial.println("-----connection closed-----");
  digitalWrite(pinLED, 1);       // LED off
 }
}

#endif
