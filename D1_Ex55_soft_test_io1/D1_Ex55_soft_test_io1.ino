//_____D1_Ex55_soft_test_io1.ino______________190105-190105_____
// Send and receive characters on software and hardware serial.
// Characters from ASCII '0' to 'z' are sent on HW serial (TX),
//   should be received on software serial (D6),
//   are send from software serial (D5) to HW serial (RX) and
//   received chars are compared to target character.
// Errors are counted and value is displayed on HW serial.
// USB (= HW serial) can be connected to watch result :)
// Hardware: 
// (1) WeMos D1 mini
// (2) Connect TX to D6, D5 to RX!
// Created by Karl Hartinger, January 05, 2019.
// Last modified: -
// Released into the public domain.
#include "src/softserial/D1_class_SoftSerial.h"

#define BAUD_RATE 115200               // 115200 = full speed ;)

#define  VERSION55  "2019-01-05 D1_Ex55_soft_test_io1"
#define  FUNCTION55 "Send char TX --> D6 => D5 --> RX and compare"
#define  PIN_SWS_TX             D5     // D5 SW Serial send
#define  PIN_SWS_RX             D6     // D6 SW Serial receive
#define  C_BEGIN               '0'     // start character
#define  C_END                 'z'     // end character

//-----SoftSerial: RX, TX, inverse_logic, bufferSize------------
SoftSerial swSeri(PIN_SWS_RX, PIN_SWS_TX, false, 256);
int        len;                        // number incomming char

//_____clear all serial buffers_________________________________
void clearBuffers()
{
 Serial.flush();                       // wait clear out buffer
 while((len=Serial.available())>0) {   // + empty
  Serial.read(); delay(1);             // | incomming
 }                                     // + buffer
 swSeri.flush();                       // wait clear out buffer
 while((len=swSeri.available())>0) {   // + empty
  swSeri.read(); delay(1);             // | incomming
 }                                     // + buffer
}

//_____SETUP____________________________________________________
void setup() {
 Serial.begin(BAUD_RATE);
 swSeri.begin(BAUD_RATE);
 Serial.println("\r\nSoftware serial test");
 Serial.println("Connect TX --> D6 and D5 --> RX");
 for(int i=5; i>=0; i--) { Serial.println(i); delay(1000); }
 Serial.println("Test started!");
 delay(100);
 clearBuffers();
 //-----clear all serial buffers for test-----------------------
}

char cout=C_BEGIN;
char ctarget=C_BEGIN;
int  errCounter=0;

void loop() {
 //-----send hardware serial------------------------------------
 if(cout>C_END) {
  cout=C_END;
  Serial.println(" ERROR. TX --> D6 and D5 --> RX connected?"); 
  delay(1000);
 }
 Serial.write(cout++);
 //-----read software serial, send software serial--------------
 if((len=swSeri.available())>0) {
  for(int i=0; i<len; i++) {           //for all chars in buffer
   char cin=swSeri.read();             // read one char
   swSeri.write(cin);                  // retransmit char 
  }
 }
 //-----read hardware serial, compare to target-----------------
 if((len=Serial.available())>0) {
  for(int i=0; i<len; i++) {           //for all chars in buffer
   char cin=Serial.read();             // read one char
   if(cin!=ctarget) errCounter++;      // wrong char received?
   ctarget++;                          // next target char
   //.....end of cycle?.........................................
   if(cin>=C_END) {
    Serial.print(" -> Errors: "); 
    Serial.println(errCounter);
    cout=C_BEGIN;
    ctarget=C_BEGIN;
    errCounter=0;
    i=len;
    delay(100);
    clearBuffers();
   }
  }
 }
}
