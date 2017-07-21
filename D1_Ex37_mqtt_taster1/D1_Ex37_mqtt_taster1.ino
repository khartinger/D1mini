//_____D1_Ex37_mqtt_taster1.ino_______________170719-170719_____
//
// Simple MQTT-Example (needs a broker!)
// * When button at D3 is pressed the value 1 is published under
//   the topic "button".
// * Messages received for topic "counter" are printed to Serial.
//
#include "D1_Ex37_mqtt_taster1.h"
#include "D1_class_Din.h"
Din button_(D3);

//_____process incoming message_________________________________
void callback(char* topic, byte* payload, unsigned int length)
{
 Serial.print("Message for topic ");
 Serial.print(topic);
 Serial.print(": ");
 for (int i = 0; i < length; i++) 
 {
  Serial.print((char)payload[i]);
 }
 Serial.println();
}

//_____setup Serial, WLAN and MQTT clients______________________
void setup() 
{
 Serial.begin(9600);
 setup_wifi();
 client.setServer(mqtt_server, 1883);
 client.setCallback(callback);
 client.subscribe("counter");
}

//_____main loop________________________________________________
void loop() 
{
 if(isConnected())
 {
  if(button_.is_falling_edge())
  {
   client.publish("button", "1", true);     // true=retain
   Serial.println("button=1");
  }
 }
}
