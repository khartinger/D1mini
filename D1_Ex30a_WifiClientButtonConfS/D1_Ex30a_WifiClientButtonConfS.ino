//_____D1_Ex30a_WifiClientButtonConfS.ino_____170224-170226_____
// Sends a request to access point 192.168.1.111 if button
//   (D3=DGPIO0) is pressed. If there is an answer, the D1mini 
//   blue LED blinks.
// For config/reset: connect TX-RX while system start
// All client functions a placed in header file
//   D1_Ex30a_WifiClientButtonConfS.h
// All config functions a placed in header file
//   D1_ConfigClientEeprom.h
// Hardware: WeMos D1 mini
//           1-Button Shield
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
const int pinButton=D5;
const int pinLED=D4;
int button_old=1;
#include "D1_Ex30a_WifiClientButtonConfS.h"
#include "D1_ConfigClientEeprom.h"

//_____setup routine____________________________________________
void setup(void){
 Serial.begin(19200);
 pinMode(pinButton, INPUT);
 pinMode(pinLED, OUTPUT);
 digitalWrite(pinLED, 1);         // *** LED off ***
 setup_config_client();
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

