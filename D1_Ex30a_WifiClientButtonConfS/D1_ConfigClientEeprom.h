//_____D1_ConfigClientEeprom.h______________170224-20170226_____
// uses: ADDR_SIZE, NAME_SIZE, SSID_SIZE, PASS_SIZE
//       sign_[3], name_[NAME_SIZE+1], ssid_[SSID_SIZE+1],
//                 pass_[PASS_SIZE+1]
//       IPAddress ip, gateway, subnet, host
#ifndef D1_CONFIGCLIENTEEPROM_H
#define D1_CONFIGCLIENTEEPROM_H
#include "EEPROM.h"
#define MAX_SEC_TO_ANSWER    20

//**************************************************************
// global value(s)/infos
//**************************************************************

//_____public functions_________________________________________
void setup_cancel_EEPROM();
void setup_config_client();

//**************************************************************
// globals and functions in this file
//**************************************************************

//_____array for default WiFi values____________________________
#define EEPROM_SIZE (ADDR_SIZE+NAME_SIZE+SSID_SIZE+PASS_SIZE)
uint8_t wdat_[EEPROM_SIZE];       // array with wlan data
int config=0;              //1=config, 2=reset, 0=eeprom/default

//_____private functions used by public functions_______________
int     config_get_serial();
int     config_isConfig();
int     config_isReset();
int     config_vars2wdat();
void    config_wdat2vars();
uint8_t config_build_checksum(uint8_t *data);

int     config_get1ip(int nr, String txt);
int     config_check_ipaddress(String sIP, IPAddress *ip);

int     config_read_eeprom(int noee2);
void    config_print_serial(uint8_t *data);
size_t  eeprom_read_block(uint8_t *data,uint32_t address,size_t len);
size_t  eeprom_write_block(uint8_t *data,uint32_t address,size_t len);

//**************************************************************
// (parts of) websites
//**************************************************************

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
// return: wifi data in vars (data from EEPROM or default)
void setup_config_client()
{
 config_vars2wdat();              // copy values to wdat_
 EEPROM.begin(EEPROM_SIZE);       // init EEPROM
 config = config_isReset();       // 0=normal|1=config|2=default
 int loc_=config_read_eeprom(config);
 if(loc_==1) Serial.println("Config data from EEPROM.   ");
        else Serial.println("Config data = default data.");
 if(config==1) config_get_serial();
 if(config==2) eeprom_write_block(wdat_, 0, EEPROM_SIZE);
 config_wdat2vars();              // wifi data from array to var
}

//**************************************************************
// (internal) functions: various
//**************************************************************

//_____get config data via Serial_______________________________
// return: all valid config data in *d_
int config_get_serial()
{
 int i=0, imax, iStart, len_;
 String sIP, txt, s2;
 String title[4]={"IP", "Subnetmask", "Gateway", "Host"};
 Serial.setTimeout(MAX_SEC_TO_ANSWER*1000);  // wait max. 5000ms
 //-----info----------------------------------------------------
 Serial.println("NOTE: When using arduino IDE change ");
 Serial.println("'Kein Zeilenende' to 'Neue Zeile' ");
 Serial.println("at bottom of Serial Monitor Window!");
 Serial.println("Input time: max. "+String(MAX_SEC_TO_ANSWER)+" sec");
 Serial.println("Send <Return> to accept default value");
 Serial.println("-------------------------------------------");
 //-----read all ips from serial--------------------------------
 imax=3;                          //3 addresses: ip,mask,gw
 if(ADDR_SIZE>16) imax=4;         //4 addresses: ip,mask,gw,host
 for(int i=0; i<imax; i++)
 {
  config_get1ip(i, title[i]);     //get 1 IPv4 address
  //.....print entered ip (input or default) to serial..........
  int iStart=4*(i+1);
  sIP=String(wdat_[iStart])+"."+String(wdat_[iStart+1])+
  "."+String(wdat_[iStart+2])+"."+String(wdat_[iStart+3]);
  Serial.println("Set to "+sIP);
 }
 //-----read mDNS name.local------------------------------------
 iStart=ADDR_SIZE;
 s2=String(name_);
 Serial.print("Input mDNS name.local (default "+s2+"): ");
 txt=Serial.readStringUntil('\n');
 len_=txt.length();
 if((len_>0)&&(len_<=NAME_SIZE))
 {
  for(i=0; i<len_; i++) wdat_[iStart+i]=txt.charAt(i);
  for(i=len_; i<NAME_SIZE; i++) wdat_[iStart+i]=0;
  s2=txt;
 }
 Serial.println("Set to "+s2);
 //-----read ssid-----------------------------------------------
 iStart=ADDR_SIZE+NAME_SIZE;
 s2=String(ssid_);
 Serial.print("Input SSID (default "+s2+"): ");
 txt=Serial.readStringUntil('\n');
 len_=txt.length();
 if((len_>0)&&(len_<=SSID_SIZE))
 {
  for(i=0; i<len_; i++) wdat_[iStart+i]=txt.charAt(i);
  for(i=len_; i<SSID_SIZE; i++) wdat_[iStart+i]=0;
  s2=txt;
 }
 Serial.println("Set to "+s2);
 //-----read password-------------------------------------------
 iStart=ADDR_SIZE+NAME_SIZE+SSID_SIZE;
 s2=String(pass_);
 Serial.print("Input SSID (default "+s2+"): ");
 txt=Serial.readStringUntil('\n');
 len_=txt.length();
 if((len_>0)&&(len_<=PASS_SIZE))
 {
  for(i=0; i<len_; i++) wdat_[iStart+i]=txt.charAt(i);
  for(i=len_; i<PASS_SIZE; i++) wdat_[iStart+i]=0;
  s2=txt;
 }
 Serial.println("Set to "+s2);
 //-----build first 4 bytes-------------------------------------
 wdat_[0]=sign_[0];
 wdat_[1]=sign_[1];
 wdat_[2]=0;
 uint8_t checksum=config_build_checksum(wdat_);
 wdat_[3]=checksum;
 //-----confirm: use the entered values-------------------------
 Serial.println("=====entered data==========================");
 config_print_serial(wdat_);
 Serial.print("Save entered data (j/n): ");
 i=MAX_SEC_TO_ANSWER*10;
 int byte_in=0; 
 while((i>0)&&(byte_in==0))       //wait for input or timeout
 {
  i--;
  if(Serial.available()>0) byte_in=Serial.read();
  delay(100);
 }
 //-----analyze input-------------------------------------------
 byte_in=toupper(byte_in);
 if(byte_in!='J')
 { //.....do not use entered data, use defaults.................
  Serial.println("N");             // show answer no
  config_vars2wdat();              // copy values to wdat_
 }
 else
 { //.....data in wdat_ ok, copy them to eeprom.................
  eeprom_write_block(wdat_, 0, EEPROM_SIZE);
  Serial.println("J\nData saved to EEPROM!");
 }
}

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
 delay(20);                       // wait for answer
 Serial.flush();                  // wait for empty outgoing buf
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
// return: 0=NO, 1=config mode, 2=reset mode (use default)
int config_isReset()
{
 int config_=1;
 Serial.println(); delay(2);      // 1. Zeilenumbruch
 config_ = config_isConfig();
 if(config_==0) 
 {
  Serial.println("==========standard mode===========");
  return config_;
 }
 //-----loop: test every 0,25sec if button is still pressed-----
 int i=12;
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

//_____copy default values into array wdat______________________
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
 if(ADDR_SIZE>16)
 {
  wdat_[16]=host[0]; wdat_[17]=host[1];
  wdat_[18]=host[2]; wdat_[19]=host[3]; 
 }
 //.....set mDNS name.local.....................................
 for(int i=0; i<NAME_SIZE; i++)
  wdat_[ADDR_SIZE+i]=name_[i];
 //.....set ssid................................................
 for(int i=0; i<SSID_SIZE; i++)
  wdat_[ADDR_SIZE+NAME_SIZE+i]=ssid_[i];
 //.....set password............................................
 for(int i=0; i<PASS_SIZE; i++)
  wdat_[ADDR_SIZE+NAME_SIZE+SSID_SIZE+i]=pass_[i];
 //.....first 4 values..........................................
 wdat_[0]=sign_[0];               // 'C'
 wdat_[1]=sign_[1];               // 'L'
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
 if(ADDR_SIZE>16)
 {
  host  =IPAddress(wdat_[16], wdat_[17], wdat_[18], wdat_[19]);
 }
 //.....set mDNS name.local.....................................
 for(int i=0; i<NAME_SIZE; i++)
  name_[i]=wdat_[ADDR_SIZE+i];
 //.....set ssid_...............................................
 for(int i=0; i<SSID_SIZE; i++)
  ssid_[i]=wdat_[ADDR_SIZE+NAME_SIZE+i];
 //.....set pass_...............................................
 for(int i=0; i<PASS_SIZE; i++)
  pass_[i]=wdat_[ADDR_SIZE+NAME_SIZE+SSID_SIZE+i];
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

//_____read one ip-Address from serial__________________________
// return: 1=new ip in wdat_, 0=no change
int config_get1ip(int nr, String txt)
{
 int i, imax, len_, newip_=0;
 String sIP;
 int iStart=4*(nr+1);
 IPAddress ip_=IPAddress();
 String s2=String(wdat_[iStart])+"."+String(wdat_[iStart+1])+
  "."+String(wdat_[iStart+2])+"."+String(wdat_[iStart+3]);
 Serial.print("Input "+txt+" (default "+s2+"): ");
 //-----read String---------------------------------------------
 sIP=Serial.readStringUntil('\n');
 len_=sIP.length();
 if(len_>0)
 { //.....check, if ip is ok....................................
  newip_=config_check_ipaddress(sIP, &ip_);
  if(newip_==1)
  {
   //.....copy ip bytes into new_ array.........................
   wdat_[iStart]=ip_[0];   wdat_[iStart+1]=ip_[1];
   wdat_[iStart+2]=ip_[2]; wdat_[iStart+3]=ip_[3];
  }
 }
 return newip_;
}

//_____check, if string sIP is a valid ip-address_______________
// return: 1=ok -> ip is valid, 0=no -> ip is invalid (0.0.0.0)
int config_check_ipaddress(String sIP, IPAddress *ip)
{
 String s1;
 long t1_;
 int posPtold=-1, posPtnew=-1;
 uint8_t ip1[4];
 *ip=IPAddress();
 //-----try to find 4 bytes-------------------------------------
 for(int i=0; i<4; i++)
 {
  posPtold=posPtnew;
  posPtnew=sIP.indexOf('.',posPtold+1);     // find (next) dot .
  if((i<3)&&(posPtnew<1)) return 0;         // not found
  s1=sIP.substring(posPtold+1, posPtnew);   // number as string
  for(int i=0; i<s1.length(); i++)          // check every digit
  {
   if(!isDigit(s1.charAt(i))) return 0;     // not a number
  }
  t1_=s1.toInt();                           // make number
  if((t1_<0)||(t1_>255)) return 0;          // value 0..255?
  ip1[i]=t1_;                               // byte ok
 }
 //-----string is valid ip--------------------------------------
 *ip=IPAddress(ip1[0], ip1[1], ip1[2], ip1[3]);
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

//_____show config (addresses and names) via serial_____________
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
 if(ADDR_SIZE>16)
 {
  s1= String(d_[16])+"."+String(d_[17])+"."+String(d_[18])+".";
  s1+=String(d_[19]);
  Serial.println("Host        : "+s1);
 }
 //-----local name----------------------------------------------
 s1="";
 for(int i=0; i<NAME_SIZE; i++)
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
  int i1=ADDR_SIZE+NAME_SIZE+i;
  d1=d_[i1];
  if(d1<32) s1+=" #"+String(d1)+" ";
  else { s1+=" "; s1.setCharAt(s1.length()-1, d1); }
 }
 Serial.println("SSID        : "+s1);
 //-----password------------------------------------------------
 s1="";
 for(int i=0; i<PASS_SIZE; i++)
 {
  int i1=ADDR_SIZE+NAME_SIZE+SSID_SIZE+i;
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
  data[i]=EEPROM.read(address+i);
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
  EEPROM.write(address+i, data[i]);
 EEPROM.commit();
 return len;
}
#endif
