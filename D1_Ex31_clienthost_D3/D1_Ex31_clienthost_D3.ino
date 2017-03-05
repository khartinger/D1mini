//_____D1_Ex31_clienthost_D3.ino______________170305-170305_____
// D1 mini tries to connect to wlan, data given in myWLAN.h
// While wlan access the blue led is on. If there is no wlan 
//   available on start, the led shines continuously.
// D1 as client: send a request to access point 192.168.1.111,
//   if button D3 (GPIO0) is pressed. (Answer see Serial)
// D1 as Host: listen to Port 80, a request is answered by
//   plain text "Hello from D1_Ex31_clienthost_D3"
// All functions:          header file D1_Ex31_clienthost_D3.h
// Hardware: WeMos D1 mini
//           1-Button Shield (button on D3)
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#define PIN_BUTTOND3         D3        // D3=GPIO0
#define PIN_BLUE_LED         D4        // D4=GPIO2
#define HTTP_PORT            80        // default for http
#define TIMEOUT_RESPONSE_MS  5000      // max. wait for server
int button_old=1;                      // old button value
WiFiClient client;
ESP8266WebServer server(HTTP_PORT);
#include "myWLAN.h"
#include "D1_Ex31_clienthost_D3.h"

//_____setup routine____________________________________________
void setup(void){
 Serial.begin(19200);             // serial: set baud rate
 Serial.println("");              // serial: empty line
 pinMode(PIN_BUTTOND3, INPUT);    // button is input
 pinMode(PIN_BLUE_LED, OUTPUT);   // blue LED pin = output
 digitalWrite(PIN_BLUE_LED, 1);   // 1 = blue LED off (!)
 setup_webclienthost();           // connect wlan, start server
}


//_____main loop________________________________________________
void loop(void){
 server.handleClient();
 int button_= digitalRead(PIN_BUTTOND3);
 if((button_==0) && (button_!=button_old))
 {
  Serial.println("button pressed!");
  loop_webclient("/");
 }
 button_old=button_;
}

