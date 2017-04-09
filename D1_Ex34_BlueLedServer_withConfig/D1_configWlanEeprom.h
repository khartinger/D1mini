//_____D1_configWlanEeprom.h__________________170226-170304_____
// Config wlan data of a server.
// Connecting TX to RX while resetting the D1 mini allows
// config mode. In this mode wlan data can be changed by 
// /config request.
// If TX is connected to RX longer than 3 sec, wlan data are
// set to default values.
//
// uses: ADDR_SIZE, MDNS_SIZE, SSID_SIZE, PASS_SIZE
//       sign_[3], name_[MDNS_SIZE+1], ssid_[SSID_SIZE+1],
//                 pass_[PASS_SIZE+1]
//       IPAddress ip, gateway, subnet, host
#ifndef D1_CONFIGWLANEEPROM_H
#define D1_CONFIGWLANEEPROM_H
#include <EEPROM.h>
#include "myWLAN.h"
#define  WAIT_FOR_CONFIG_RESET 3       // >3s => wlan data reset
#ifndef BAUDRATE
 #define BAUDRATE 9600 
#endif
extern ESP8266WebServer server;


//**************************************************************
// global value(s)/infos
//**************************************************************
//_____name of (external) website to return after config________
extern void setup_wlan();         //webserver setup
extern void handleRoot();         //return website after config


//_____public functions_________________________________________
void setup_cancel_EEPROM();
void setup_config_wlan();
void handle_config_server();

//**************************************************************
// globals and functions in this file
//**************************************************************

//_____array for default WiFi values____________________________
#define EEPROM_SIZE (ADDR_SIZE+MDNS_SIZE+SSID_SIZE+PASS_SIZE)
uint8_t wdat_[EEPROM_SIZE];// array with wlan data
int configWLAN=0;          //1=config, 2=reset, 0=eeprom/default

//_____private functions used by public functions_______________
int     config_isConfig();
int     config_isReset();
int     config_vars2wdat();
void    config_wdat2vars();
uint8_t config_build_checksum(uint8_t *data);

String  config_page1_server_input();
long    config_check_input_byte(int nr);
int     config_params2wdat();

int     config_read_eeprom(int noee2);
void    config_print_serial(uint8_t *data);
size_t  eeprom_read_block(uint8_t *data,uint32_t address,size_t len);
size_t  eeprom_write_block(uint8_t *data,uint32_t address,size_t len);

//**************************************************************
// (parts of) websites
//**************************************************************

const char html_config_head[] PROGMEM=
 "<!DOCTYPE html PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\"\n"
 "\"http://www.w3.org/TR/html4/loose.dtd\">\n"
 "<html>\n<head>\n<title>WiFi config</title>\n"
 "<meta http-equiv=\"Content-Type\" content=\"text/html; "
 "charset=iso-8859-1\">"
 "<style>\n"
 "#in1 { width:100%; box-sizing:border-box; }\n"
 "</style>\n"
 "\n</head>\n<body>\n";

const char html_config_foot[] PROGMEM=
 "\n</body>\n</html>";

const char page9_not_in_config_mode[] PROGMEM=
 "<html><head><title>WiFi config</title></head>\n<body>\n"
 "<h3>Error</h3>Not in config mode.<br>\n"
 "<a href=\"/\"><button>Weiter...</button></a>"
 "\n</body></html>\n";

const char page7_unknown_submit_error[] PROGMEM=
 "<html><head><title>WiFi config</title></head>\n<body>\n"
 "<h3>Error</h3>Unknown submit error.<br>\n"
 "<a href=\"/\"><button>Weiter...</button></a>"
 "\n</body></html>\n";

const char page2_config_input_ok[] PROGMEM=
 "<html><head><title>WiFi config</title></head>\n<body>\n"
 "<h3>Success</h3>Input data accepted. <br>"
 "Restart WiFi with new parameters.<br>\n"
 "<form action=\"/config\" method=\"get\">\n"
 "<input type=\"submit\" name=\"ex\" value=\"Restart\"> "
 "\n</form>\n</body></html>\n";

const char page1_config_input_body[] PROGMEM=
 "<h3>Config D1mini</h3>\n"
 "<form action=\"/config\" method=\"get\">\n"
 "<table border=1>\n"
 "<tr><td>IPv4-Adresse</td><td>";

const char page1_config_input_in3[] PROGMEM=
 "<input type=\"text\" size=3 maxlength=3 name=";

//**************************************************************
// public functions
//**************************************************************
//_____invalidate EEPROM config data____________________________
// set first 2 bytes in EEPROM to 0 (instead of IP)
void setup_cancel_EEPROM()
{
 EEPROM.begin(EEPROM_SIZE);       // init EEPROM
 EEPROM.write(0, 0);              // make EEPROM data invalid
 EEPROM.write(1, 0);              // make EEPROM data invalid
 EEPROM.commit();
}

//_____only on start: check if config ip is required____________
// return: wifi data in vars (data from EEPROM or wdat_)
void setup_config_wlan()
{
 if(!Serial)
 {
  Serial.begin(BAUDRATE);         // serial: set baud rate
 }
 config_vars2wdat();              // copy values to wdat_
 EEPROM.begin(EEPROM_SIZE);       // init EEPROM
 configWLAN = config_isReset();   // 0=normal|1=config|2=default
 int loc_=config_read_eeprom(configWLAN);
 if(loc_==1) Serial.println("Config data from EEPROM.   ");
        else Serial.println("Config data = default data.");
 if(configWLAN==2) eeprom_write_block(wdat_, 0, EEPROM_SIZE);
 config_print_serial(wdat_);     // serial: show wlan data
 config_wdat2vars();             // copy wlan data to vars
 if(configWLAN==1) server.on("/config", handle_config_server);
}

//_____process request and send answer__________________________
void handle_config_server() 
{
 int check_=0;
 //uint8_t data_[EEPROM_SIZE];
 //-----reset after config changed------------------------------
 if(configWLAN==4)
 {
  configWLAN=0;
  handleRoot();
  return;
 }
 //-----config not allowed?-------------------------------------
 if(configWLAN==0)
 {
  server.send(200, "text/html", page9_not_in_config_mode);
  Serial.println("Request 9: not in config mode.");
  return;
 }
 //-----restart WiFi?-------------------------------------------
 if(configWLAN==3)
 {
  configWLAN=4;                   // turn off config mode
  WiFi.disconnect();
  delay(10);
  setup_wlan();
  return;  
 }
 //-----unknown config mode (should never be true ;)------------
 if((configWLAN!=1) && (configWLAN!=2))
 {
  String s2="Unknown config mode "+String(configWLAN)+".";
  String s1=String(html_config_head);
  s1+="<h3>Input Error</h3>";
  s1+=s2+"<br>\n";
  s1+="<a href=\"/\"><button>Weiter...</button></a>";
  s1+=String(html_config_foot);
  server.send(200, "text/html", s1);
  Serial.println("Request 8: "+s2);  
  return;
 }
 int paramnr_ex=(ADDR_SIZE-4)+3;
 //-----reset or config, not from input-page => show input page-
 if(!server.argName(paramnr_ex).equals("ex"))
 {
  config_read_eeprom(configWLAN);
  server.send(200,"text/html",config_page1_server_input());
  Serial.println("Request 1: show input page.");
  return;
 }
 //-----abort web page input------------------------------------
 if(server.arg(paramnr_ex).indexOf("Abbrech")>=0)
 {
  configWLAN=0;                  // config finished
  Serial.println("Konfiguration wurde abgebrochen.");
  handleRoot();
  return;
 }  
 //-----wrong parameter for "ex"--------------------------------
 if(server.arg(paramnr_ex).indexOf("bernehmen")<1)
 {
  server.send(200, "text/html", page7_unknown_submit_error);
  Serial.println("Request 7: unknown submit error.");
  return;
 }
 //-----try to apply (web) params-------------------------------
 check_=config_params2wdat();   
 Serial.println("Uebernehmen: check_="+String(check_));
 if(check_!=1)
 {
  String s2="Input check error: "+String(check_)+".";
  String s1=String(html_config_head);
  s1+="<h2>Input Error</h2>";
  s1+=s2;
  s1+=String(html_config_foot);
  server.send(200, "text/html", s1);
  Serial.println("Request 4: "+s2);
 }
 //-----copy data to WiFi vars----------------------------------
 configWLAN=3;
 eeprom_write_block(wdat_,0,EEPROM_SIZE);
 config_wdat2vars();
 server.send(200, "text/html", page2_config_input_ok);
 Serial.println("Request 2: config input data ok. WiFi restart.");
}

//**************************************************************
// (internal) functions: various
//**************************************************************

//_____ad: is reset button pressed on start?____________________
// send teststring one time and check, if received it back
// called by config_isReset()
// return: 0=NO, 1=config key pressed
int config_isConfig()
{
 int config_=1;
 //-----clean buffers-------------------------------------------
 Serial.flush();                  // wait for empty outgoing buf
 while(Serial.available())        // + empty incomming
  Serial.read();                  // + buffer
 //-----test, if config is wanted-------------------------------
 String teststring="config";      
 int len_=teststring.length();    // length = 6
 Serial.println(teststring);      // send test string
 delay(25);                       // wait for answer
 int anz=Serial.available();      // characters received?
 if(anz!=len_+2)                  // teststring + \r\n
  config_=0;                      // nothing/wrong received
 else
 {
  char answer_[len_+2];           // len_+2 = 8
  Serial.readBytes(answer_,len_); // 6="config".length();
  answer_[len_]=0;                // ad 0 = end of string
  String s2=String(answer_);      // convert to string
  if(!teststring.equals(s2))      // received string ok?
   config_=0;                     // wrong test string received
 }
 return config_;
}

//_____is reset button pressed on start for more than 3 sec?____
// calls config_isConfig() more times
// called by setup_config_server()
// return: 0=NO, 1=config mode, 2=reset mode (use wdat_)
int config_isReset()
{
 int config_=1;
 Serial.println(); delay(5);      // 1. Zeilenumbruch
 config_ = config_isConfig();
 if(config_==0) 
 {
  Serial.println("==========standard mode===========");
  return config_;
 }
 //-----loop: test every 0,25sec if button is still pressed-----
 int i=4*WAIT_FOR_CONFIG_RESET;
 do
 {
  i--;
  delay(230);                     // config_isConfig waits 20ms
  config_=config_isConfig();
 } while((config_==1) && (i>0));
 //-----which end of loop?--------------------------------------
 config_=1;
 if(i<=0)
 { 
  config_=2;
  Serial.println("============RESET mode============");
 }
 else
  Serial.println("===========CONFIG mode============");
 return config_; 
}

//_____copy default values into array wdat_______________
// uses all globals
int config_vars2wdat()
{
 //.....set addresses...........................................
 wdat_[4]=ip[0];       wdat_[5]=ip[1];
 wdat_[6]=ip[2];       wdat_[7]=ip[3];
 wdat_[8] =subnet[0];  wdat_[9] =subnet[1];
 wdat_[10]=subnet[2];  wdat_[11]=subnet[3];
 wdat_[12]=gateway[0]; wdat_[13]=gateway[1];
 wdat_[14]=gateway[2]; wdat_[15]=gateway[3];
 wdat_[16]=host[0];    wdat_[17]=host[1];
 wdat_[18]=host[2];    wdat_[19]=host[3];
 //.....set mDNS name.local.....................................
 for(int i=0; i<MDNS_SIZE; i++)
  wdat_[ADDR_SIZE+i]=mdns_[i];
 //.....set ssid................................................
 for(int i=0; i<SSID_SIZE; i++)
  wdat_[ADDR_SIZE+MDNS_SIZE+i]=ssid_[i];
 //.....set password............................................
 for(int i=0; i<PASS_SIZE; i++)
  wdat_[ADDR_SIZE+MDNS_SIZE+SSID_SIZE+i]=pass_[i];
 //.....first 4 values..........................................
 wdat_[0]=sign_[0];               // 'S';
 wdat_[1]=sign_[1];               // 'V';
 wdat_[2]=0;
 uint8_t checksum=config_build_checksum(wdat_);
 wdat_[3]=checksum;
}

//_____transfer wifi data from array to vars____________________
// uses all globals
void config_wdat2vars()
{
 //.....set addresses...........................................
 ip     =IPAddress(wdat_[4],  wdat_[5],  wdat_[6],  wdat_[7]);
 subnet =IPAddress(wdat_[8],  wdat_[9],  wdat_[10], wdat_[11]);
 gateway=IPAddress(wdat_[12], wdat_[13], wdat_[14], wdat_[15]);
 host   =IPAddress(wdat_[16], wdat_[17], wdat_[18], wdat_[19]);
 //.....set mDNS name.local.....................................
 for(int i=0; i<MDNS_SIZE; i++)
  mdns_[i]=wdat_[ADDR_SIZE+i];
 //.....set ssid_...............................................
 for(int i=0; i<SSID_SIZE; i++)
  ssid_[i]=wdat_[ADDR_SIZE+MDNS_SIZE+i];
 //.....set pass_...............................................
 for(int i=0; i<PASS_SIZE; i++)
  pass_[i]=wdat_[ADDR_SIZE+MDNS_SIZE+SSID_SIZE+i];
}

//_____build checksum___________________________________________
// return: checkbyte
uint8_t config_build_checksum(uint8_t *data)
{
 int i;
 uint8_t checksum=0;
 for(i=4; i<EEPROM_SIZE; i++) 
  checksum=checksum^data[i];
 return checksum;
}

//_____build web page with default values_______________________
String config_page1_server_input()
{
 //-----convert default names to string-------------------------
 char c;
 String nloc_="";
 int i=0, i0=ADDR_SIZE;
 for(i=0; i<MDNS_SIZE; i++)
 { c=(char)wdat_[i0+i]; if(c!=0) nloc_+=c;
 }
 String ssid_="";
 i0=i0+i;
 for(i=0; i<SSID_SIZE; i++)
 { c=(char)wdat_[i0+i]; if(c!=0) ssid_+=c;
 }
 String pwd_="";
 i0=i0+i;
 for(i=0; i<PASS_SIZE; i++)
 { c=(char)wdat_[i0+i]; if(c!=0) pwd_+=c;
 }
 //-----build web page------------------------------------------
 String s1="";
 s1+=String(html_config_head);
 s1+=String(page1_config_input_body);
 s1+=String(page1_config_input_in3);
 s1+="\"i0\" value=\""+String(wdat_[4])+"\">.";
 s1+=String(page1_config_input_in3);
 s1+="\"i1\" value=\""+String(wdat_[5])+"\">.";
 s1+=String(page1_config_input_in3);
 s1+="\"i2\" value=\""+String(wdat_[6])+"\">.";
 s1+=String(page1_config_input_in3);
 s1+="\"i3\" value=\""+String(wdat_[7])+"\">";
 s1+="</td></tr>\n<tr>";
 s1+="<td>Subnetzmaske</td><td>";
 s1+=String(page1_config_input_in3);
 s1+="\"m0\" value=\""+String(wdat_[8])+"\">.";
 s1+=String(page1_config_input_in3);
 s1+="\"m1\" value=\""+String(wdat_[9])+"\">.";
 s1+=String(page1_config_input_in3);
 s1+="\"m2\" value=\""+String(wdat_[10])+"\">.";
 s1+=String(page1_config_input_in3);
 s1+="\"m3\" value=\""+String(wdat_[11])+"\">";
 s1+="</td></tr>\n<tr>";
 s1+="<td>Gateway</td><td>";
 s1+=String(page1_config_input_in3);
 s1+="\"g0\" value=\""+String(wdat_[12])+"\">.";
 s1+=String(page1_config_input_in3);
 s1+="\"g1\" value=\""+String(wdat_[13])+"\">.";
 s1+=String(page1_config_input_in3);
 s1+="\"g2\" value=\""+String(wdat_[14])+"\">.";
 s1+=String(page1_config_input_in3);
 s1+="\"g3\" value=\""+String(wdat_[15])+"\">";
 s1+="</td></tr>\n";
 s1+="<td>Host</td><td>";
 s1+=String(page1_config_input_in3);
 s1+="\"h0\" value=\""+String(wdat_[16])+"\">.";
 s1+=String(page1_config_input_in3);
 s1+="\"h1\" value=\""+String(wdat_[17])+"\">.";
 s1+=String(page1_config_input_in3);
 s1+="\"h2\" value=\""+String(wdat_[18])+"\">.";
 s1+=String(page1_config_input_in3);
 s1+="\"h3\" value=\""+String(wdat_[19])+"\">";
 s1+="</td></tr>\n";
 //-----text inputs---------------------------------------------
 s1+="<tr><td>mDNS: Local name &nbsp; </td><td>";
 s1+="<input id=\"in1\" type=\"text\" size=20 maxlength=20 ";
 s1+="name=\"n\" value=\""+nloc_+"\"></td></tr>\n";
 s1+="<tr><td>ssid_</td><td>";
 s1+="<input id=\"in1\" type=\"text\" size=20 maxlength=20 ";
 s1+="name=\"s\" value=\""+ssid_+"\"></td></tr>\n";
 s1+="<tr><td>Passwort</td><td>";
 s1+="<input id=\"in1\" type=\"password\" size=20 maxlength=20 ";
 s1+="name=\"p\" value=\""+pwd_+"\"></td></tr>\n</table>\n<br>\n";
 //-----buttons-------------------------------------------------
 s1+="<input type=\"submit\" name=\"ex\" value=\"Abbrechen\"> ";
 s1+="&nbsp; \n";
 s1+="<input type=\"submit\" name=\"ex\" value=\"\r &Uuml;bernehmen!\">";
 s1+=String(html_config_foot);
 return s1;
}

//_____check if input (string) is value from 0..255_____________
// return: 0..255 if ok, <0 on error
long config_check_input_byte(int nr)
{
 long t1_;
 String s1=server.arg(nr);
 for(int i=0; i<s1.length(); i++)
 {
  if(!isDigit(s1.charAt(i))) return -((nr+1)*10+i+2);
 }
 t1_=s1.toInt();
 if((t1_<0)||(t1_>255)) return -((nr+1)*10+1);
 return t1_;
}

//_____check website params and copy them to wdat_______________
// return: 1=data ok, <0 error
int config_params2wdat()
{
 int i, i0=0, len_=0;
 long t1_;
 String s1;
 uint8_t tmp_[EEPROM_SIZE];
 //----first 4 values-------------------------------------------
 tmp_[i0++]=sign_[0];             //'S';
 tmp_[i0++]=sign_[1];             //'V';
 tmp_[i0++]=0;
 tmp_[i0++]=0;
 //-----check IP input------------------------------------------
 for(i=0; i<4; i++)
 {
  s1="i"+String(i);
//  Serial.print("s1="+s1+" -> ");
  if(!server.argName(i).equals(s1)) return -(i+1)*10;
  t1_=config_check_input_byte(i); if(t1_<0) return t1_;
  tmp_[i0++]=t1_;
//  Serial.println("check ok");
 }
 //-----check subnetmask input----------------------------------
 for(i=0; i<4; i++)
 {
  s1="m"+String(i);
  if(!server.argName(i+4).equals(s1)) return -(i+5)*10;
  t1_=config_check_input_byte(i+4); if(t1_<0) return t1_;
  tmp_[i0++]=t1_;
 }
 //-----check gateway input-------------------------------------
 for(i=0; i<4; i++)
 {
  s1="g"+String(i);
  if(!server.argName(i+8).equals(s1)) return -(i+9)*10;
  t1_=config_check_input_byte(i+8); if(t1_<0) return t1_;
  tmp_[i0++]=t1_;
 }
 //-----check host input----------------------------------------
 for(i=0; i<4; i++)
 {
  s1="h"+String(i);
  if(!server.argName(i+12).equals(s1)) return -(i+13)*10;
  t1_=config_check_input_byte(i+12); if(t1_<0) return t1_;
  tmp_[i0++]=t1_;
 }
 //-----check mDNS (local name)---------------------------------
 if(!server.argName(16).equals("n")) return -120;
 s1=server.arg(16);
 len_=s1.length();
 if(len_>MDNS_SIZE) return -121;
 for(i=0; i<len_; i++) tmp_[i0++]=s1[i];
 for(i=len_; i<MDNS_SIZE; i++) tmp_[i0++]=0;
 //-----check ssid----------------------------------------------
 if(!server.argName(17).equals("s")) return -130;
 s1=server.arg(17);
 len_=s1.length();
 if(len_>SSID_SIZE) return -131;
 for(i=0; i<len_; i++) tmp_[i0++]=s1[i];
 for(i=len_; i<SSID_SIZE; i++) tmp_[i0++]=0;
 //-----check password------------------------------------------
 if(!server.argName(18).equals("p")) return -140;
 s1=server.arg(18);
 len_=s1.length();
 if(len_>PASS_SIZE) return -141;
 for(i=0; i<len_; i++) tmp_[i0++]=s1[i];
 for(i=len_; i<PASS_SIZE; i++) tmp_[i0++]=0; 
 //.....build and save checksum.................................
 tmp_[3]=config_build_checksum(tmp_);
 Serial.println("getParams: checksum="+String(tmp_[3]));
 //-----copy input to parameter---------------------------------
 for(i=0; i<EEPROM_SIZE; i++)
  wdat_[i]=tmp_[i];
 return 1;
}

//_____(try to) read default values from eeprom_________________
// noee2:  2 = no eeprom
// return: 1 = data from EEPROM read (ok), 
//         0 = eeprom data invalid, def_ used instead
int config_read_eeprom(int noee2)
{
 int useeeprom=0;
 uint8_t data[EEPROM_SIZE];
 //-----valid data in EEPROM?-----------------------------------
 if((EEPROM.read(0)==sign_[0])&&(EEPROM.read(1)==sign_[1])
     &&(noee2!=2))
 {
  int anz=eeprom_read_block(data,0,EEPROM_SIZE);
  if(anz==EEPROM_SIZE)
  {  
   //.....build checksum........................................
   int checksum=config_build_checksum(data);
   //.....checksum and saved checksum equal?....................
   if(data[3]==checksum) useeeprom=1;
  }
 }
 //-----copy eeprom data to wdat_ if data valid-----------------
 if(useeeprom==1)
 {
  //-----config or EEPROM-error: use default values-------------
  for(int i=0; i<EEPROM_SIZE; i++) 
   wdat_[i]=data[i];
 }
 return useeeprom;
}

//_____show config via serial___________________________________
void config_print_serial(uint8_t *d_)
{
 char c;
 uint8_t d1;
 String s1="    ";
 s1.setCharAt(0,d_[0]);
 s1.setCharAt(2,d_[1]);
 s1+= String(d_[2])+" "+String(d_[3]);
 Serial.println("Kennung 0..3: "+s1);
 s1= String(d_[4])+"."+String(d_[5])+"."+String(d_[6])+".";
 s1+=String(d_[7]);
 Serial.println("IPv4-Adresse: "+s1);
 s1= String(d_[8])+"."+String(d_[9])+"."+String(d_[10])+".";
 s1+=String(d_[11]);
 Serial.println("Subnetzmaske: "+s1);
 s1= String(d_[12])+"."+String(d_[13])+"."+String(d_[14])+".";
 s1+=String(d_[15]);
 Serial.println("Gateway     : "+s1);
 s1= String(d_[16])+"."+String(d_[17])+"."+String(d_[18])+".";
 s1+=String(d_[19]);
 Serial.println("Host        : "+s1);

 //-----local name----------------------------------------------
 s1="";
 for(int i=0; i<MDNS_SIZE; i++)
 {
  d1=d_[ADDR_SIZE+i];
  if(d1<32) s1+=" #"+String(d1)+" ";
  else { s1+=" "; s1.setCharAt(s1.length()-1, d1); }
 }
 Serial.println("Local name  : "+s1);
 //-----ssid----------------------------------------------------
 s1="";
 for(int i=0; i<SSID_SIZE; i++)
 {
  int i1=ADDR_SIZE+MDNS_SIZE+i;
  d1=d_[i1];
  if(d1<32) s1+=" #"+String(d1)+" ";
  else { s1+=" "; s1.setCharAt(s1.length()-1, d1); }
 }
 Serial.println("SSID        : "+s1);
 //-----password------------------------------------------------
 s1="";
 for(int i=0; i<PASS_SIZE; i++)
 {
  int i1=ADDR_SIZE+MDNS_SIZE+SSID_SIZE+i;
  d1=d_[i1];
  if(d1<32) s1+=" #"+String(d1)+" ";
  else { s1+=" "; s1.setCharAt(s1.length()-1, d1); }
 }
 Serial.println("Passwort    : "+s1);
}

//==============================================================
// (internal) functions for eeprom read/write
//==============================================================

//_____read a block from eeprom_________________________________
// uses: EEPROM_SIZE
// return: number of read bytes or -1|-2|-3 on error
size_t eeprom_read_block(uint8_t *data, uint32_t address, 
 size_t len){
 int i;
 //-----check input---------------------------------------------
 if(len==0)    return -1;
 if(len<0)     return -2;
 if(address<0) return -3;
 if((address+len)>EEPROM_SIZE)
 {
  len=EEPROM_SIZE-address;        // or return -4
 }
 //-----read bytes----------------------------------------------
 for(i=0; i<len; i++)
 {
  data[i]=EEPROM.read(address+i);
 }
 return len;
}

//_____write a block to eeprom__________________________________
// uses: EEPROM_SIZE
// return: number of written bytes or -1|-2|-3 on error
size_t eeprom_write_block(uint8_t *data, uint32_t address, 
 size_t len){
 int i;
 //-----check input---------------------------------------------
 if(len==0)    return -1;
 if(len<0)     return -2;
 if(address<0) return -3;
 if((address+len)>EEPROM_SIZE)
 {
  len=EEPROM_SIZE-address;        // or return -4
 }
 //-----write bytes---------------------------------------------
 for(i=0; i<len; i++)
 {
  EEPROM.write(address+i, data[i]);
 }
 EEPROM.commit();
 return len;
}
#endif
