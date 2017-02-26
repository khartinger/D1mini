//_____D1_Ex16_WifiAPCounterInterruptD5Oled.h______20160911_____
#ifndef D1_EX16_WIFIAPCOUNTERINTERRUPTD5OLED_H
#define D1_EX16_WIFIAPCOUNTERINTERRUPTD5OLED_H
const char* ssid = "D1mini           ";// 17 chars
const char* password = "12345678";     // min. 8 chars or ""
IPAddress ip(192,168,1,111);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);
#define PIN_BUTTON D5                  // PIN_BUTTON=D5=GPIO14
#define OLED_RESET D3                  // OLED_RESET=D3=GPIO0
Adafruit_SSD1306 display(OLED_RESET);
WiFiServer server(80);
unsigned long requestCounter;
unsigned long endMillis;

//_____show counter value and client ip on oled-display_________
void display_oled(String sCounter, String sLine56)
{
 int x=32-6*sCounter.length();         // counter start position
 display.clearDisplay();               // Clear display-buffer
 display.drawRect(0,0,63,29,WHITE);    // border around counter
 display.setTextSize(2);               // char size 12x16 pixel
 display.setCursor(x,8);               // center counter text
 display.println(sCounter);            // print counter
 display.setTextSize(1);               // char size 6x8 pixel
 display.setCursor(0,33);              // write to line 5
 display.println(sLine56);             // write line 5 (+ 6)
 display.display();                    // show buffer
}

//_____returns line with client ip and signal strength__________
String getLine56(WiFiClient client)
{
 IPAddress ipc=client.remoteIP();
 String sIPc = ipc.toString();
 String sRssi = String(WiFi.RSSI());
 String sLine56 = sIPc + " " + sRssi+"dBm";
 return sLine56;
}

//_____increment counter by button______________________________
void doInterrupt(void)
{
 if(digitalRead(PIN_BUTTON)==0)
 { //-----falling edge------------------------------------------
  requestCounter++;
  String sCounter = String(requestCounter);
  String sLine56 = "--local---          ";
  display_oled(sCounter, sLine56);
  endMillis = millis()+2000;
  Serial.println("Falling Edge: "+sCounter);
 }
 else
 { //-----rising edge-------------------------------------------
  if(millis() > endMillis)
  {
   requestCounter=0;
   String sCounter = String(requestCounter);
   String sLine56 = "--reset---          ";
   display_oled(sCounter, sLine56); 
   Serial.println("Rising Edge: "+sCounter);
  }
 }
}

//_____start access point_______________________________________
void setup_accesspoint()
{
 requestCounter=0;
 WiFi.mode(WIFI_AP);
 WiFi.softAPConfig(ip, gateway, subnet);
 WiFi.softAP(ssid, password);
 server.begin();
 //-----Infos to oled display and Serial------------------------
 String sIP=ip.toString();
 String sSSID=String(ssid);
 Serial.println("\nAccess point: ssid=\""+sSSID+"\", ip="+sIP);
 display_oled(String(requestCounter), "Access "+sIP);
}

//_____build the OK response http header________________________
String getHeaderOK(String sResp)
{
 String sHeader = "HTTP/1.1 200 OK\r\n";
 sHeader += "Content-Length: ";
 sHeader += sResp.length();
 sHeader += "\r\n";
 sHeader += "Content-Type: text/html\r\n";
 //sHeader += "Content-Type: text/plain\r\n";
 sHeader += "Connection: close\r\n";
 sHeader += "\r\n";
 return sHeader;
}

//_____build the ERROR answer (header + response)_______________
String getAnswerError()
{
 String sHeader, sResp;
 sResp  ="<html><head><title>404 Not Found</title></head>\n";
 sResp += "<body><h1>Not Found</h1>The requested URL was not ";
 sResp += "found on D1mini.</p></body></html>";
 sHeader  = "HTTP/1.1 404 Not found\r\n";
 sHeader += "Content-Length: ";
 sHeader += sResp.length();
 sHeader += "\r\n";
 sHeader += "Content-Type: text/html\r\n";
 sHeader += "Connection: close\r\n";
 sHeader += "\r\n";
 return (sHeader + sResp);
}

//_____Analyze request, do action and build response____________
// return: HTML or plain text (*) or empty string on error
// (*) depends on Content-Type: text/... in Header
String doRequestHTML(String sRequest)
{
 String sResp="";
 //-----devide request into path and parameters-----------------
 // Syntax is e.g. GET /?led=ON HTTP/1.1
 String sPath="", sParam="",  sGetstart="GET ";
 int iStart,iEndSpace,iEndQuest;
 iStart = sRequest.indexOf(sGetstart);
 if (iStart>=0)
 {
  iStart += sGetstart.length();
  iEndSpace = sRequest.indexOf(" ",iStart);
  iEndQuest = sRequest.indexOf("?",iStart);
  //.....are there parameters?..................................
  if(iEndSpace>0)
  {
   if(iEndQuest>0)
   { // yes, there are parameters
    sPath  = sRequest.substring(iStart,iEndQuest);
    sParam = sRequest.substring(iEndQuest+1,iEndSpace); //+1 -?
   }
   else
   { // NO parameters
    sPath  = sRequest.substring(iStart,iEndSpace);
   }
  }
 }
 //-----show param to serial------------------------------------
 Serial.println("Path: "+sPath+", Param: "+sParam);
 //-----check for supported paths (connect with &&)-------------
 if(!sPath.equals("/") && 
    !sPath.equals("/resetcounter")) return sResp;
 //-----start of html page--------------------------------------
 String sTitle="Access point counter";
 sResp += "<html><head><title>"+sTitle+"</title></head><body>\n";
 //-----do action and body of html page-------------------------
 if(sPath.equals("/resetcounter"))
 {
  requestCounter=0;
 } 
 sResp += "<h1>"+String(requestCounter)+"</h1>";
  
 //-----end of html page----------------------------------------
 sResp += "\n</body></html>";
 return sResp;
}

//_____send answer (responce) to client_________________________
void handleClient() {
 WiFiClient client = server.available();
 if (!client) {
  return;
 }
 //-----client present: wait for client data--------------------
 digitalWrite(pinLED, 0);                   // *** LED on  ***
 requestCounter++;                          // increase counter
 String sCounter = String(requestCounter);
 String sLine56=getLine56(client);
 Serial.println(sCounter + " | New client, ip=" + sLine56);
 display_oled(sCounter, sLine56);
 
 unsigned long timeout = millis()+250;
 while(!client.available() && (millis()<timeout) )
 {
  delay(1);
 }
 if(millis()>timeout) 
 { 
  Serial.println("client connection time-out!");
  digitalWrite(pinLED, 1);                  // *** LED off ***   
  return; 
 }
 //-----read first line of request------------------------------
 String sRequest = client.readStringUntil('\r');
 //Serial.println(sRequest);
 client.flush();
 //-----stop client, if request is empty------------------------
 if(sRequest=="")
 {
  Serial.println("empty request! - stopping client");
  client.stop();
  digitalWrite(pinLED, 1);                  // *** LED off ***
  return;
 }
 //-----analyse line AND build HTML-String----------------------
 String sHeader;
 String sResp = doRequestHTML(sRequest);
 if(sResp.equals("")) { sHeader = getAnswerError();   }
                 else { sHeader = getHeaderOK(sResp); }
 //-----send response to client---------------------------------
 client.print(sHeader);
 client.print(sResp);
 //-----stop client and finish handle client--------------------
 client.stop();
 if(requestCounter<1)
 {
  String sCounter = String(requestCounter);
  Serial.println(sCounter + " | counter reset");
  display_oled(sCounter, sLine56);
 }
 Serial.println("-----Client disonnected----------------");
 digitalWrite(pinLED, 1);                   // *** LED off *** 
}
#endif
