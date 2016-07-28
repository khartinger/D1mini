//_____D1_Ex11_WifiClientSec_______________________20160727_____
// Sends every 5 seconds a request to server 192.168.0.123
// and shows answer at Serial (57600 baud)
// All client functions a placed in header file
//   D1_Ex11_WifiClientSec.h
// Hardware: WeMos D1 mini
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include "D1_Ex11_WifiClientSec.h"

//_____setup routine____________________________________________
void setup(void){
 Serial.begin(57600);
 setup_webclient();
}

//_____main loop________________________________________________
void loop(void){
 WiFiClient client;
 if (!client.connect(host, httpPort)) {
  Serial.println("ERROR: connection failed!");
 }
 else
 {
  //-----connected, send request--------------------------------
  Serial.println("\nConnected to " + String(host));
  Serial.print("Signal strength: ");
  int rssi = WiFi.RSSI();
  Serial.print(rssi);
  Serial.println(" dBm");
  String uri="/";                 // uri for request
  String request="GET "+ uri +  " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n";
  client.print(request);
  delay(10);
  //-----slow: read all lines of server reply, print to Serial---
  Serial.println("-----Response:----------------------");
  while(client.available()){
   String line = client.readStringUntil('\r');
   Serial.print(line);
  }
  Serial.println();
  Serial.println("-----connection closed, wait 5s -----");
  delay(5000);
 }
}
