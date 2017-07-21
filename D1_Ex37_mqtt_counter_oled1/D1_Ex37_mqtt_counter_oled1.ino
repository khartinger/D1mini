//_____D1_Ex37_mqtt_counter_oled1.ino___________170720-170720_____
//
// Simple MQTT-Example (needs a broker!)
// * When message "button" with payload 1 is received, a counter
//   is incremented, the value is displayed on oled shield and
//   printed to Serial. (Payload 0 resets the counter.)
// * After that, a message "counter" is published with the 
//   counter value.
//
#include "D1_Ex37_mqtt_counter_oled1.h"
#include "D1_class_DisplayKH.h"
DisplayKH     display_;                // 
#define MESSAGE_MAXLEN       127
char msg[1+MESSAGE_MAXLEN];

//_____display counter value on oled____________________________
void display_counter(String sCounter)
{
 display_.screen13(1,sCounter,'c',false);
 display_.screen13(2,"MQTT");
 display_.screen13(3,"counter");
 display_.screen13(4,"170720 KH");
 display_.display();
}

//_____process incoming message_________________________________
void callback(char* topic, byte* payload, unsigned int length)
{
 String sTopic=String(topic);
 //-----print message to Serial---------------------------------
 Serial.print("Message for topic ");
 Serial.print(sTopic);
 Serial.print(": ");
 for (int i = 0; i < length; i++) 
 {
  Serial.print((char)payload[i]);
 }
 Serial.print(" --> ");
 //-----process message button----------------------------------
 if(sTopic=="button")
 {
  if(payload[0]=='0') requestCounter=0;
  if(payload[0]=='1') requestCounter++;
  String sCounter=String(requestCounter);
  Serial.print("requestCounter = "+sCounter);
  display_counter(sCounter);
  snprintf(msg, MESSAGE_MAXLEN, "%ld", requestCounter);
  client.publish("counter", msg, true);    // true=retain
 }
 Serial.println();
}

//_____setup Serial, WLAN and MQTT clients______________________
void setup() 
{
 Serial.begin(9600); Serial.println("");
 display_counter(String(requestCounter));
 //-----setup WLAN and mqtt-------------------------------------
 setup_wifi();
 client.setServer(mqtt_server, 1883);
 client.setCallback(callback);
 client.subscribe("button");
}

//_____main loop________________________________________________
void loop() 
{
 isConnected();
 delay(20);
}
