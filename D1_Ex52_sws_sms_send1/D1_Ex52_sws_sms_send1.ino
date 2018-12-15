//_____D1_Ex52_sws_sms_send1.ino______________181215-181215_____
// If button D3 is pressed a test sms is sent using
// SIM800C GSM GPRS module STM32.
// While SMS sending, the blue LED is turned on.
// If an error occurred while initializing SIM module, 
// the blue led blinks quickly and system is stopped.
// SIM-Connection  : Software Serial @ D5 (=TX), D6 (=RX)
// DEBUG info to PC: Hardware Serial @ TX, RX
//
// Hardware: (1) WeMos D1 mini
//           (2) Battery Shield for WEMOS D1 mini
//           (3) Selfmade SIM800C 9pol ProtoBoard Shield with
//               SIM800C GSM GPRS module STM32
//           (4) 1-Button Shield
// Created by Karl Hartinger, December 15, 2018.
// Last modified: -
// Released into the public domain.

#define  TEL_NUMBER1    "0680xxxxx"  // CHANGE TO YOUR OWN #!!
#define  VERSION52      "2018-12-15 D1_Ex52_sws_sms_send1"
#define  FUNCTION52     "Press D3 to send a SMS"
#define  DEBUG52              true     // or false
#define  DEBUG52_SHOW_CRLF   false     // print # instead \r, ~ \n
#define  PIN_BUTTON             D3     // D3 is default button
#define  PIN_LED_BLUE           D4     // pin blue led @ D1 mini
#define  PIN_SWS_TX             D5     //pin SoftwareSerial send
#define  PIN_SWS_RX             D6     // SoftwareSerial receive
#define  CRLF                 "\r"     // sim carriage return
#define  SIM800_WAIT_MS       4000     // sim command timeout
#define  SIM800_MEM           "ME"     // ME=modem, SM=sim card
#include <SoftwareSerial.h>

SoftwareSerial SeriSW(PIN_SWS_RX, PIN_SWS_TX);   // Pins RX, TX
int      button3;                      // button value
int      buttonOld;                    // old value of button

//***** Helper functions ***************************************

//_____Serial: print # insted of \r, ~ insted of \n_____________
void serialprint(String sRet)
{
 String s1=sRet;
 if(DEBUG52_SHOW_CRLF) {
  s1.replace("\n", "~");
  s1.replace("\r", "#");
 }
 Serial.print("len=");
 Serial.print(sRet.length());
 Serial.println(": "+s1);
}

//_____count occurence of a specific string in another string___
int countOccurrence1in2(String sFind, String sBasic)
{
 int iPos=0;
 int iNum=0;
 int iLen=sFind.length();
 while(sBasic.indexOf(sFind,iPos)>=0) {
  iPos=sBasic.indexOf(sFind, iPos)+iLen;
  iNum++;
 }
 return iNum;
}

//***** Send SMS functions *************************************

//_____send a command to SIM800C________________________________
// sEnd  : End-String (or character as String)
// numEnd: how often should end string be found in answer
// return: modem answer string or "" on error
String smsSendCmd(String cmd, String sEnd, int numEnd)
{
 int    i=0;                           // receive byte counter
 char   c;                             // received byte
 String sRet="";                       // answer string
 String cmd2=cmd+CRLF;                 // command + carriage ret
 bool   finished=false;                // command finished
 //-----just for safety: empty receive buffer-------------------
 while(SeriSW.available()) { SeriSW.read(); }
 delay(10);                            // wait a little bit
 //-----send command--------------------------------------------
 SeriSW.print(cmd2);                   // send command
 //-----receive answer------------------------------------------
 unsigned long tEnd=SIM800_WAIT_MS+millis();     // end time
 while(!finished && (millis()<tEnd))
 {
  delay(50);                           // wait a little bit 
  while(SeriSW.available())
  {
   c=SeriSW.read();                    // read char
   sRet+=String((char)c);              // add char to answer
   if(countOccurrence1in2(sEnd,sRet)>=numEnd)
    finished=true;                     // finished
  }
 }
 return sRet;                          // return answer string
}

//_____send a standard command to SIM800C_______________________
String smsSendCmd(String cmd) { 
 return(smsSendCmd(cmd, String(CRLF), 2));
}

//_____set text mode____________________________________________
String smsBegin(String mem)
{
 String sCmd, sRet;                    // command, return string
 //-----finish old sms, if a send-error occurred----------------
 smsSendCmd("\x1A");                  // just for safety
 //-----turn echo on (better for debug)-------------------------
 sCmd="ATE1";                         // echo 0=off, 1=on
 sRet=smsSendCmd(sCmd);               // send command
 if(DEBUG52) serialprint(sRet);        // show answer
 if(sRet.indexOf("OK")<0) return("Abort: Error while "+sCmd);
 //-----set sms text format-------------------------------------
 sCmd="AT+CMGF=1";                     // use text format
 sRet=smsSendCmd(sCmd);                // send command
 if(DEBUG52) serialprint(sRet);        // show answer
 if(sRet.indexOf("OK")<0) return("Abort: Error while "+sCmd);
 //-----set preferred message storage to modem (ME)-------------
 sCmd="AT+CPMS=\""+mem+"\",\""+mem+"\",\""+mem+"\"";
 sRet=smsSendCmd(sCmd);                // send command
 if(DEBUG52) serialprint(sRet);        // show answer
 if(sRet.indexOf("OK")<0) return("Abort: Error while "+sCmd);
 //-----configuration message routing---------------------------
 sCmd="AT+CNMI=2,1,2,1,0";             // use text format
 sRet=smsSendCmd(sCmd);                // send command
 if(DEBUG52) serialprint(sRet);        // show answer
 if(sRet.indexOf("OK")<0) return("Abort: Error while "+sCmd);
 return("OK");
}

//_____send a sms_______________________________________________
String smsSendSMS(String number, String text)
{
 String sCmd, sRet;                    // command, return string
 String txt2=text+"\x1A";              // sms text (end 1A)
 //-----finish old sms, if a send-error occurred----------------
 smsSendCmd("\x1A");                  // just for safety
 //-----send sms------------------------------------------------
 sCmd="AT+CMGS=\""+number+"\""+CRLF;   // command send sms
 sRet=smsSendCmd(sCmd,">",1);          // send cmd to modem
 if(sRet.indexOf(">")>=0)              // input sign received
  sRet=smsSendCmd(txt2,CRLF,6);        // send text to modem
 else
  sRet="ERROR: No input sign >";       // error message
 return sRet;
}

//***** absolutely necessary functions *************************

//_____SETUP____________________________________________________
void setup() {
 pinMode(PIN_BUTTON, INPUT);           // pin button = input
 pinMode(PIN_LED_BLUE, OUTPUT);        // pin blue led = output
 digitalWrite(PIN_LED_BLUE,1);         // blue led off
 buttonOld=digitalRead(PIN_BUTTON);    // button start value
 //-----software serial-----------------------------------------
 SeriSW.begin(9600);                   // start software serial
 SeriSW.listen();                      // listen to soft SeriSW
 SeriSW.flush();                       // wait clear out buffer
 while(SeriSW.available()) {           // + empty incomming
  SeriSW.read(); delay(1);             // + buffer
 } 
 //-----setup hardware serial (baudrate, clear buffer)----------
 Serial.begin(9600);                   // init Serial
 Serial.println("\r\n"+String(VERSION52)+"\r\n"+String(FUNCTION52));
 //-----check sim module----------------------------------------
 Serial.println("-----Init Modem-----");// show OK message
 String sRet=smsBegin(SIM800_MEM);      // ME=module, SM=SIM
 if(sRet.indexOf("OK")<0) {
  serialprint(sRet);                   // show error message
  Serial.println("***ERROR init SIM - System stopped! ***");
  while(true) {
   digitalWrite(PIN_LED_BLUE,0); delay(100); // blue led on
   digitalWrite(PIN_LED_BLUE,1); delay(100); // blue led off
  }
 }
 Serial.println("-----Modem OK-----");// show OK message
}

//_____LOOP_____________________________________________________
void loop() {
 String sRet;                          // command, return string
 int buttonX=digitalRead(PIN_BUTTON);  // 1. read button value
 delay(25);                            // wait button bouncing
 int buttonY=digitalRead(PIN_BUTTON);  // 2. read button value
 if(buttonX==buttonY) button3=buttonX; // no pulse spike
 if((buttonOld==1)&&(button3==0))      // falling edge
 {
  digitalWrite(PIN_LED_BLUE,0);        // blue led on
  Serial.println("-----Button pressed!-----");
  String sNum=String(TEL_NUMBER1);      // 
  String sSMS=String(VERSION52)+"\r\nUp-Time: "+String(millis())+"ms";
  sRet=smsSendSMS(sNum, sSMS);          // send SMS
  serialprint(sRet);                    // show answer
   Serial.println("-----Sent finished-----");
  digitalWrite(PIN_LED_BLUE,1);       // blue led off
 }
 buttonOld=button3;                    // remember old value
 delay(100);                           // wait a little bit
}

