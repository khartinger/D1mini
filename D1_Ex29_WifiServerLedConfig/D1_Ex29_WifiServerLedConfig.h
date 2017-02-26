//_____D1_Ex29_WifiServerLedConfig.h_______________20170222_____
#ifndef D1_EX29_WIFISERVERLEDCONFIG_H
#define D1_EX29_WIFISERVERLEDCONFIG_H

//_____values also used by config file__________________________
extern void handle_config_server();
#define   ADDR_SIZE     16
#define   NAME_SIZE     20
#define   SSID_SIZE     20
#define   PASS_SIZE     20
char      sign_[3]="SV";
char      name_[NAME_SIZE+1]="D1mini111";
char      ssid_[SSID_SIZE+1]="D1mini           "; // 17 chars
char      pass_[PASS_SIZE+1]="12345678";          // min. 8 char
IPAddress ip(192,168,1,110);
IPAddress gateway(192,168,0,1);
IPAddress subnet(255,255,252,0);
ESP8266WebServer server(80);

//_____(parts of) websites______________________________________
const char page_led_switcher[] PROGMEM=
 "<html><head><title>LED switcher</title></head>\n<body>\n"
 "<h2>Switch blue LED</h2>\n"
 "<a href=\"/?led=on\"><button>LED on</button></a> &nbsp; \n"
 "<a href=\"/?led=off\"><button>LED off</button></a>"
 "\n</body></html>\n";
 
//_____process request and send answer__________________________
void handleRoot() {
 //-----process request: switch blue LED on or off--------------
 String sLed=server.argName(0);
 sLed.toLowerCase();
 if(sLed.equals("led"))
 {
  String sArg=server.arg(0);
  sArg.toLowerCase();
  if(sArg.equals("on"))  { digitalWrite(PIN_LED, 0); }
  if(sArg.equals("off")) { digitalWrite(PIN_LED, 1); }
 }
 //-----send answer page----------------------------------------
 server.send(200, "text/html", page_led_switcher);
}

//_____send answer if file (uri) not found______________________
void handleNotFound(){
 String s = "File Not Found\nURI: " + server.uri();
 server.send(404, "text/plain", s);
 Serial.println("Request: "+s);
}

//_____start the webserver______________________________________
void setup_webserver()
{
 WiFi.disconnect();
 delay(1);
 WiFi.begin(ssid_, pass_);
 WiFi.config(ip, gateway, subnet);  // skipp for dhcp
 Serial.println("-----WiFi params set--------------"); 
 Serial.print  ("Try to connect to WLAN: ");
 Serial.println(ssid_);
 Serial.print  ("Password  : ");
 Serial.println(pass_);
 Serial.print  ("Local name: ");
 Serial.println(name_);
 Serial.print  ("Server IP address: ");
 Serial.println(WiFi.localIP());
 Serial.print  ("Server subnet    : ");
 Serial.println(WiFi.subnetMask());
 Serial.print  ("Server gateway   : ");
 Serial.println(WiFi.gatewayIP());
 Serial.println("----------------------------------"); 
 //-----Wait for connection-------------------------------------
 int i=0;
 while (WiFi.status() != WL_CONNECTED) {
  delay(100);
  Serial.print(".");
  if(++i > 50) { i=0; Serial.println(); }
 }
 //-----send connection info to serial interface----------------
 Serial.println("");
 Serial.print  ("Connected to WLAN: ");
 Serial.println(ssid_);
 Serial.print  ("Server IP address: ");
 Serial.println(WiFi.localIP());
 Serial.print  ("Server subnet    : ");
 Serial.println(WiFi.subnetMask());
 Serial.print  ("Server gateway   : ");
 Serial.println(WiFi.gatewayIP());
 //-----start mDNS----------------------------------------------
 if (MDNS.begin(name_)) {
  Serial.println("MulticastDNS name: "+String(name_)+".local"); 
  Serial.println("MDNS responder started");
 }
 //-----handles to answer the request---------------------------
 server.on("/", handleRoot);
 server.on("/config", handle_config_server);
 server.onNotFound(handleNotFound);
 //-----start server--------------------------------------------
 server.begin();
 Serial.println("HTTP server started");
}

#endif
