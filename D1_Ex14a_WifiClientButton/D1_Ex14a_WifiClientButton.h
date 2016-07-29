//_____D1_Ex14a_WifiClientButton.h_________________20160729_____
#ifndef D1_EX14A_WIFICLIENTBUTTON_H
#define D1_EX14A_WIFICLIENTBUTTON_H
const char* ssid = "D1mini           ";// 17 chars
const char* password = "12345678";     // min. 8 chars or ""
IPAddress ip(192,168,1,101);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);
char* host = "192.168.1.1";    // or "http://..."
int httpPort=80;
WiFiClient client;

//_____start the webserver______________________________________
void setup_webclient()
{
 if(DEBUG) Serial.println("\n-----Setup wifi connection-----");
 WiFi.mode(WIFI_STA);
 WiFi.config(ip, gateway, subnet);  // skipp for dhcp
 WiFi.begin(ssid, password);
 //-----Wait for connection-------------------------------------
 while (WiFi.status() != WL_CONNECTED) {
  delay(500);
  if(DEBUG) Serial.print(".");
 }
 //-----send connection info to serial interface----------------
 if(DEBUG)
 {
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
}

//_____send a request and show response at Serial---------------
void loop_webclient(String uri)
{
 if (!client.connect(host, httpPort)) {
  if(DEBUG) Serial.println("ERROR: connection failed!");
 }
 else
 {
  //-----connected, send request--------------------------------
  digitalWrite(pinLED, 0);       // LED on
  if(DEBUG)
  {
   Serial.println("\nConnected to " + String(host));
   Serial.print("Signal strength: ");
   int rssi = WiFi.RSSI();
   Serial.print(rssi);
   Serial.println(" dBm");
  }
  String request="GET "+ uri +  " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" + 
                 "Connection: close\r\n\r\n";
  client.print(request);
  delay(10);
  if(DEBUG) Serial.println("-----Response:-------------");
/* 
  //-----quick check of response--------------------------------
  if(DEBUG)
  {
   if(client.available()) Serial.println("OK");             // |
                     else Serial.println("ERROR");          // |
  }
*/
  //-----slow: read all lines of server reply, print to Serial---
  if(DEBUG)
  {
   String line="";	
   while(client.available()){
    line = client.readStringUntil('\r');
    Serial.print(line);
   }
   Serial.println();
   Serial.println("-----connection closed-----");
  }
  //-----stop client and turn LED off---------------------------
  client.stop();
  digitalWrite(pinLED, 1);       // LED off
 }
}

#endif
