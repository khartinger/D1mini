//_____D1_Ex11_WifiClientSec.h_____________________20160727_____
#ifndef D1_EX11_WIFICLIENTSEC_H
#define D1_EX11_WIFICLIENTSEC_H
#include "myWifiData.h"  // contains private *ssid and *password
//const char *ssid = "*****";
//const char *password = "*****";
IPAddress ip(192,168,0,101);
IPAddress gateway(192,168,0,1);
IPAddress subnet(255,255,255,0);
const char* host = "192.168.0.123";    // or "http://..."
int httpPort=80;

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
#endif
