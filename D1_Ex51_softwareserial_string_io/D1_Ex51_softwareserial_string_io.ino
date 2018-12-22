//_____D1_Ex51_softwareserial_string_io.ino___181101-181101_____
// Simulation of "read a string" from SoftwareSerial
//  (9600 Bd, D6=Rx, D5=Tx), convert it to upper
//  and send it back (echo).
// Received string is also shown on (hardware) Serial.
// Blue LED blinks with 2Hz to demonstrate main loop is done.
// See also https://www.arduino.cc/en/Reference/Serial
// Hardware: 
// (1) WeMos D1 mini
// (2) PC with RS232-3V3-Converter and Terminalsoftware
//     Connect D1mini Tx(D5)-RxD Rx(D6)-TxD GND-GND, 3V3-3V3
// Important: You MUST use 3.3V for D1 mini pins!!!!
// Created by Karl Hartinger, November 01, 2018.
// Last modified: -
// Released into the public domain.
#include <SoftwareSerial.h>

#define  PIN_LED_BLUE           D4     // pin blue led @ D1 mini
#define  PIN_SWS_RX             D6     // pin SoftwareSerial receive
#define  PIN_SWS_TX             D5     // pin SoftwareSerial send

SoftwareSerial SeriSW(PIN_SWS_RX,PIN_SWS_TX); // Pins RX, TX

//_____add character to string__________________________________
// return: true = string finished
String readStringUntil(String s1, char c, char cEnd)
{
 if(c!=cEnd) s1+=String(c);
 return s1;
}

void setup() {
 pinMode(PIN_LED_BLUE, OUTPUT);
 pinMode(PIN_LED_BLUE, OUTPUT);        // led pin = output
 Serial.begin(9600);                   // start hardware serial
 Serial.println("\r\nWaiting for serial input...");
 SeriSW.begin(9600);                   // start software serial
 SeriSW.println("\r\nWaiting for serial input...");
 SeriSW.listen();
}

String s1;
int i=0;
 
void loop() {
 char c;
 int len=SeriSW.available();
 if(len)
 {
  while(len>0)
  {
   len--;
   c=SeriSW.read();
   String s2=readStringUntil(s1, c, '\r');
   if(s1==s2)
   {
    s2.toUpperCase();                   // to upper
    s2=s1+" --> "+s2;                   // ouput string
    Serial.println(s2);                 // hardware serial
    SeriSW.println(s2);                 // software serial
    s1="";                              // new string
    len=0;
   }
   else s1=s2;
  }
 }
 delay(25);
 if((++i)>5) {
  i=0; 
  digitalWrite(PIN_LED_BLUE, digitalRead(PIN_LED_BLUE)^1);
 }
}
