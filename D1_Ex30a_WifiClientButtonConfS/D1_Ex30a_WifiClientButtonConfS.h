//_____D1_Ex30a_WifiClientButtonConf.h________170224-170226_____
// Client functions for *.ino file and D1_ConfigClientEeprom.h
#ifndef D1_EX30A_WIFICLIENTBUTTONCONFIG_H
#define D1_EX30A_WIFICLIENTBUTTONCONFIG_H

//_____values also used by config file__________________________
extern void handle_config_server();
#define   ADDR_SIZE     20
#define   NAME_SIZE     20
#define   SSID_SIZE     20
#define   PASS_SIZE     20
char      sign_[3]="CL";
char      name_[NAME_SIZE+1]="D1mini";
char      ssid_[SSID_SIZE+1]="D1mini           ";// 17 chars
char      pass_[PASS_SIZE+1]="12345678";    //min. 8 chars or ""
IPAddress ip(192,168,1,101);
IPAddress subnet(255,255,252,0);
IPAddress gateway(192,168,0,1);
IPAddress host(192,168,1,111);

//**************************************************************
// globals and functions in this file
//**************************************************************
#define TIMEOUT_RESPONSE_MS  5000
int httpPort=80;
WiFiClient client;

void setup_webclient();
void loop_webclient(String uri);

//**************************************************************
// public functions
//**************************************************************

//_____start the webserver______________________________________
void setup_webclient()
{
 Serial.println("\n-----Setup wifi connection-----");
 WiFi.disconnect();
 delay(10);
 WiFi.mode(WIFI_STA);
 WiFi.config(ip, gateway, subnet);     // skipp for dhcp
 WiFi.begin(ssid_, pass_);
 //-----Wait for connection-------------------------------------
 int i=0;
 while (WiFi.status() != WL_CONNECTED) {
  delay(100);
  Serial.print(".");
  if(++i>50) { i=0; Serial.println(""); }
 }
 //-----send connection info to serial interface----------------
 Serial.println("");
 Serial.print("Connected to ");
 Serial.println(ssid_);
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
 //-----(try to) connect to host--------------------------------
 String shost=host.toString();
 if (!client.connect(host, httpPort)) {
  Serial.println("ERROR: connection failed!");
  delay(300);
  return;
 }
 //-----connected, send request---------------------------------
 digitalWrite(pinLED, 0);         // *** LED on ***
 Serial.println("\nConnected to " + shost);
 Serial.print("Signal strength: ");
 int rssi = WiFi.RSSI();
 Serial.print(rssi);
 Serial.println(" dBm");
 String request="GET "+ uri +  " HTTP/1.1\r\n" +
                "Host: " + shost + "\r\n" + 
                "Connection: close\r\n\r\n";
 client.print(request);
 delay(100);
 //-----wait for server to response with timeout----------------
 int timeout_=TIMEOUT_RESPONSE_MS/10;
 while((!client.available())&&(timeout_>0))
 {
  delay(10);
  timeout_--;
 }
 //-----read data, if available before timeout------------------
 if(timeout_>0)
 {
  Serial.println("-----Response:----------------");
/* 
  //-----quick check of response--------------------------------
  if(DEBUG)
  {
   if(client.available()) Serial.println("OK");             // |
                     else Serial.println("ERROR");          // |
  }
*/
  //-----slow: read all lines of server reply, print to Serial--
  String line="";
  while(client.available()){
   line = client.readStringUntil('\r');
   Serial.print(line);
  }
  Serial.println();
  Serial.println("-----connection closed--------");
 }
 else
 {
  Serial.println("-----No Response: Timeout-----");
 }
 //-----stop client and turn LED off----------------------------
 client.stop();
 digitalWrite(pinLED, 1);         // *** LED off ***
}

#endif
