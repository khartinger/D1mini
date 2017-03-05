//_____D1_Ex31_clienthost_D3.h________________170305-170305_____
// Client functions for *.ino file
#ifndef D1_EX31_CLIENTHOST_D3_H
#define D1_EX31_CLIENTHOST_D3_H

//_____send answer (responce) to client_________________________
void handleRoot()
{
 digitalWrite(PIN_BLUE_LED, 0);        // *** blue LED on  ***
 String s1="Hello from D1_Ex31_clienthost_D3";
 server.send(200, "text/plain", s1);
 digitalWrite(PIN_BLUE_LED, 1);        // *** blue LED off ***
}

//_____start the webclient and webserver________________________
void setup_webclienthost()
{
 digitalWrite(PIN_BLUE_LED, 0);        // *** blue LED on  ***
 Serial.println("\n-----Setup wifi connection-----");
 WiFi.mode(WIFI_STA);
 WiFi.config(ip, gateway, subnet);          // skipp for dhcp
 WiFi.begin(ssid_, pass_);
 //-----Wait for connection-------------------------------------
 int i=0;
 while (WiFi.status() != WL_CONNECTED) {
  delay(100);
  Serial.print(".");
  if(++i>50) { i=0; Serial.println(""); }
 }
 //-----send connection info to serial interface----------------
 Serial.println("\r\nConnected to "+String(ssid_));
 Serial.println("Client IP address: "+WiFi.localIP().toString());
 //-----setup host----------------------------------------------
 server.on("/", handleRoot);
 server.begin();
 digitalWrite(PIN_BLUE_LED, 1);        // *** blue LED off ***
}

//_____send a request and show response at Serial---------------
void loop_webclient(String uri)
{
 digitalWrite(PIN_BLUE_LED, 0);        // *** blue LED on  ***
 //-----(try to) connect to host--------------------------------
 String shost=host.toString();
 if (!client.connect(host, HTTP_PORT)) {
  Serial.println("ERROR: connection failed!");
  delay(300);
  return;
 }
 //-----connected, send request---------------------------------
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
  Serial.println("-----request sent - response:--------------");
  //-----slow: read all lines of server reply, print to Serial--
  String line="";
  while(client.available()){
   line = client.readStringUntil('\r');
   Serial.print(line);
  }
  Serial.println();
  Serial.println("-----connection closed---------------------");
 }
 else
 {
  Serial.println("-----request sent - NO response: Timeout---");
 }
 //-----stop client---------------------------------------------
 client.stop();
 digitalWrite(PIN_BLUE_LED, 1);        // *** blue LED off ***
}
#endif
