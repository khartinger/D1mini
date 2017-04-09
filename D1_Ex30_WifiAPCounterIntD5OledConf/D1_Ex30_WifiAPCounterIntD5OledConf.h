//_____D1_Ex30_WifiAPCounterIntD5OledConf.h________20170222_____
#ifndef D1_EX30_WIFIAPCOUNTERINT5OLEDCONF_H
#define D1_EX30_WIFIAPCOUNTERINT5OLEDCONF_H

//**************************************************************
//     values (also) used by config file
//**************************************************************
//.....handle = startpoint of config............................
extern void handle_config_server(); //process config
//.....must names for functions in this file....................
void setup_webserver();
void handleRoot();
#define   ADDR_SIZE     16
#define   NAME_SIZE     20
#define   SSID_SIZE     20
#define   PASS_SIZE     20
char      sign_[3]="IP";
char      name_[NAME_SIZE+1]="D1mini_AP111";
char      ssid_[SSID_SIZE+1]="D1mini           "; // 17 chars
char      pass_[PASS_SIZE+1]="12345678";          // min. 8 char
IPAddress ip(192,168,1,123);
IPAddress gateway(192,168,0,1);
IPAddress subnet(255,255,252,0);
ESP8266WebServer server(80);

//**************************************************************
// globals and functions in this file
//**************************************************************
os_timer_t myTimer;
#define TIMER_DELAY 2000               // ms = 2s
unsigned long requestCounter;

//_____function prototypes______________________________________
void handleRoot();
void handleResetCounter();
void handleNotFound();
void display_oled(String sCounter, String sLine56);
String getLine56();
void timer_interrupt(void *pArg);
void io_interrupt(void);
void setup_softAP();
void setup_webserver();

//**************************************************************
// (parts of) websites
//**************************************************************

const char pageHandleNotFound[] PROGMEM=
 "<html><head><title>404 Not Found</title></head>\n"
 "<body><h1>Not Found</h1>The requested URL was not "
 "found on D1mini.</body></html>";

const char pageHandleResetCounter[] PROGMEM=
 "<html><head><title>Reset Counter</title></head>\n"
 "<body><h1>0</h1></body></html>";

const char pageHandleRootHead[] PROGMEM=
 "<html><head><title>Reset Counter</title></head>\n"
 "<body><h1>";

const char pageHandleRootFoot[] PROGMEM=
 "</h1></body></html>";

//**************************************************************
// handle functions
//**************************************************************

//_____send answer (responce) to client_________________________
void handleRoot() 
{
 digitalWrite(PIN_LED, 0);                  // *** LED on  ***
 requestCounter++;                          // increase counter
 String sCounter = String(requestCounter);
 String sLine56=getLine56();
 Serial.println(sCounter + " | New client, ip=" + sLine56);
 display_oled(sCounter, sLine56);
 //-----send answer---------------------------------------------
 String s1=String(pageHandleRootHead);
 s1+=sCounter;
 s1+=String(pageHandleRootFoot);
 server.send(200, "text/html", s1);
 Serial.println("-----Client disonnected----------------");
 digitalWrite(PIN_LED, 1);                  // *** LED off *** 
}

//_____reset counter____________________________________________
void handleResetCounter()
{
 requestCounter=0;
 String sCounter = String(requestCounter);
 String sLine56=getLine56();
 display_oled(sCounter, sLine56);
 server.send(200, "text/html", pageHandleResetCounter);
 Serial.println("Request -> Counter reset");
}

//_____send answer if file (uri) not found______________________
void handleNotFound()
{
 server.send(404, "text/html", String(pageHandleNotFound));
 Serial.println("Request -> HandleNotFound");
}

//==============================================================
// OLED = Display functions
//==============================================================

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
String getLine56()
{
 String sIPc = server.client().remoteIP().toString();
 String sRssi = String(WiFi.RSSI());
 String sLine56 = sIPc + " " + sRssi+"dBm";
 return sLine56;
}

//==============================================================
// Interrupt functions for reset button
//==============================================================

//_____timer to reset counter, if button is pressed 2s__________
void timer_interrupt(void *pArg) {
 requestCounter=0;
 String sCounter = String(requestCounter);
 String sLine56 = "--reset---          ";
 display_oled(sCounter, sLine56); 
 Serial.println(sLine56);
}

//_____increment counter by button______________________________
void io_interrupt(void)
{
 if(digitalRead(PIN_BUTTON)==0)
 { //-----falling edge = Button pressed-------------------------
  requestCounter++;
  String sCounter = String(requestCounter);
  String sLine56 = "--local---          ";
  display_oled(sCounter, sLine56);
  //.....start timer............................................
  os_timer_disarm(&myTimer);                     //stopp timer
  os_timer_setfn(&myTimer, timer_interrupt, NULL); //no param
  os_timer_arm(&myTimer, TIMER_DELAY, false);    //2000ms, 1x
  Serial.println("Falling Edge: "+sCounter);
 }
 else
 { //-----rising edge = Button released-------------------------
  os_timer_disarm(&myTimer);                     //stopp timer
  String sCounter = String(requestCounter);
  Serial.println("Rising Edge: "+sCounter);
 }
}

//==============================================================
// network/server functions
//==============================================================
void setup_softAP() { setup_webserver(); }

//_____start access point_______________________________________
void setup_webserver()
{
 WiFi.disconnect();
 delay(1);
 requestCounter=0;
 WiFi.mode(WIFI_AP_STA);
 WiFi.softAPConfig(ip, gateway, subnet);
 WiFi.softAP(ssid_, pass_);
 //-----Infos to oled display and Serial------------------------
 String sIP=WiFi.softAPIP().toString();
 String sSSID=String(ssid_);
 display_oled(String(requestCounter), "Access "+sIP);
 //-----send connection info to serial interface----------------
 Serial.println("");
 Serial.print  ("Access point ssid: ");
 Serial.println(ssid_);
 Serial.print  ("Server IP address: ");
 Serial.println(sIP);
 Serial.print  ("Server subnet    : ");
 Serial.println(subnet.toString());
 Serial.print  ("Server gateway   : ");
 Serial.println(gateway.toString());
 //-----start mDNS----------------------------------------------
 if (MDNS.begin(name_)) {
  Serial.println("MulticastDNS name: "+String(name_)+".local"); 
  Serial.println("MDNS responder started");
 }
 //-----handles to answer the request---------------------------
 server.on("/", handleRoot);
 server.on("/resetcounter", handleResetCounter);
 server.on("/config", handle_config_server);
 server.onNotFound(handleNotFound);
 //-----start server--------------------------------------------
 server.begin();
 Serial.println("HTTP server started");
}
#endif
