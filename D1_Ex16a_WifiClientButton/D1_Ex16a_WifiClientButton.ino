//_____D1_Ex16a_WifiClientButton___________________20160729_____
// Sends a request to access point 192.168.1.1 if button
//   (D3=DGPIO0) is pressed. If there is an answer, the D1mini 
//   blue LED blinks.
// IF DEBUG is 1, an answer is sent to Serial (115200 baud)
// All client functions a placed in header file
//   D1_Ex14a_WifiClientButton.h
// Hardware: WeMos D1 mini
//           1-Button Shield
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#define DEBUG 0
const int pinButton=D3;
const int pinLED=D4;
int button_old=1;
#include "D1_Ex16a_WifiClientButton.h"

//_____setup routine____________________________________________
void setup(void){
 if(DEBUG) Serial.begin(115200);
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
  if(DEBUG) Serial.println("button pressed!");
  loop_webclient("/");
 }
 button_old=button_;
}

