//_____D1_Ex50_softwareserial_bytes_io.ino____181101-181101_____
// Read byte(s) from SoftwareSerial (9600 Bd, D6=Rx, D5=Tx), 
// convert it to upper and send it back (echo).
// Received bytes are also shown on (hardware) Serial
// Blue LED blinks with 2Hz to demonstrate main loop is working.
// Hardware: 
// (1) WeMos D1 mini
// (2) PC with RS232-3V3-Converter and Terminalsoftware
//     Connect D1mini Tx(D5)-RxD Rx(D6)-TxD GND-GND, 3V3-3V3
// Important: You MUST use 3.3V for D1 mini pins!!!!
// Created by Karl Hartinger, November 01, 2018.
// Last modified: -
// Released into the public domain.
#include <SoftwareSerial.h>

#define  BUFFER_SIZE            80     // i/o-buffer
#define  PIN_LED_BLUE           D4     // pin blue led @ D1 mini
#define  PIN_SWS_RX             D6     // pin SoftwareSerial receive
#define  PIN_SWS_TX             D5     // pin SoftwareSerial send

SoftwareSerial SeriSW(PIN_SWS_RX,PIN_SWS_TX); // Pins RX, TX
uint8_t buffer[BUFFER_SIZE];

void setup() {
 pinMode(PIN_LED_BLUE, OUTPUT);        // led pin = output
 Serial.begin(9600);                   // start hardware serial
 Serial.println("\r\nWaiting for serial input...");
 SeriSW.begin(9600);                   // start software serial
 SeriSW.println("\r\nWaiting for serial input...");
}

void loop() {
 SeriSW.listen();
 size_t len = SeriSW.available();
 if(len)
 {
  Serial.print("\r\nlen="); Serial.println(len); 
  //-----read available bytes-----------------------------------
  if(len>BUFFER_SIZE) len=BUFFER_SIZE; // check for buffer size
  SeriSW.readBytes(buffer,len);        // read all to buffer
  //-----convert to upper---------------------------------------
  for(int i=0; i<len; i++)
  {
   Serial.print((char)buffer[i]);      // show input char
   buffer[i]=toupper(buffer[i]);       // convert char
  }
  Serial.print(" --> ");               // for a better display
  //-----write bytes back---------------------------------------
  for(int i=0; i<len; i++)
  { 
   Serial.write(buffer[i]);            //send to hardware serial
   SeriSW.write(buffer[i]);            //send to software serial
  }
 }
 //-----blink---------------------------------------------------
 digitalWrite(PIN_LED_BLUE, digitalRead(PIN_LED_BLUE)^1);
 delay(250);
}
