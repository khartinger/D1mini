//_____D1_Ex12_WifiClientButton____________________20160727_____
// Sends a request to server 192.168.0.123 if button (D3=DGPIO0)
//   is pressed. If ther is an answer, the D1mini blue LED 
//   blinks and answer is sent to Serial (57600 baud)
// All client functions a placed in header file
//   D1_Ex12_WifiClientButton.h
// Hardware: WeMos D1 mini
//           1-Button Shield
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
const int pinButton=D3;
const int pinLED=D4;
int button_old=1;
#include "D1_Ex12_WifiClientButton.h"

//_____setup routine____________________________________________
void setup(void){
 Serial.begin(57600);
 pinMode(pinButton, INPUT);
 pinMode(pinLED, OUTPUT);
 digitalWrite(pinLED, 1);       // LED off
 setup_webclient();
}

//_____main loop________________________________________________
void loop(void){
 int button_= digitalRead(pinButton);
 if((button_==0) && (button_!=button_old))
 {
  Serial.println("button pressed!");
  loop_webclient("/");
 }
 button_old=button_;
}

