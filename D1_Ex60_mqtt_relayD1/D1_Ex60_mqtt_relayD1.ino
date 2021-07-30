//_____D1_Ex60_mqtt_relayD1.ino__________________khartinger_____
// This program for the D1 mini or ESP32 D1 mini implements a
// relay controlled via MQTT using the PubSubClient class.
// Function of this program:
// [1]   Connect to given WiFi and MQTT broker.
// [2]   If connected, turn on blue LED.
// [3]   Subscribe topic "relay/1/set" payload 0|1|-1.
// [4]   If the topic is received, ...
// [4.1] ...switch the relay 0=off, 1=on, -1=toggle.
// [4.2] ...send a message with topic "relay/1/ret" and 
//          payload new relay state (0=off, 1=on, -1=toggle).
// [5]   If connection is lost, D1 mini tries to reconnect.
//
// Hardware: 
// (1) WeMos D1 mini OR ESP32 D1 mini
// (2) Relais shield @ D1
//
// Important: Example needs a MQTT-broker!
// Created by Karl Hartinger, July 30, 2021.
// Changes:
// 2021-07-30 New
// Released into the public domain.

#define D1MINI          1              // ESP8266 D1mini +pro
//#define ESP32D1         2              // ESP32 D1mini

#if defined(ESP8266) || defined(D1MINI)
 #include <ESP8266WiFi.h>              // network connection
 #define PIN_LED        D4             // D4=IO2
 #define LED_ON         0              // LED on
 #define LED_OFF        1              // LED off
 #define PIN_RELAY      D1             // D1 -> 22
#endif
#if defined(ESP32) || defined(ESP32D1)
 #include <WiFi.h>                     // network connection
 #define PIN_LED        2              // D4=IO2
 #define LED_ON         1              // LED on
 #define LED_OFF        0              // LED off
 #define PIN_RELAY      22             // D1 -> 22
#endif
#include "src/PubSubClient.h"

#define TOPIC_SET            "relay/1/set"
#define TOPIC_RET            "relay/1/ret"
#define MESSAGE_MAXLEN       127
#define MQTT_RECONNECT_MS    4000

//.....Update these with values suitable for your network.......
const char* ssid = "Raspi11";
const char* password = "12345678";
const char* mqtt_server = "10.1.1.1";
String clientId=String("D1mini_Relay1");

WiFiClient espClient;
PubSubClient client(espClient);
long millis_lastTryToConnect = 0;
int relayState=0;                           // relay off

//_____connect to the WiFi network______________________________
void setup_wifi()
{
 delay(10);
 //-----try to connect to WLAN----------------------------------
 Serial.println("\nConnecting to "+String(ssid));
 WiFi.begin(ssid, password);
 int i=50;
 while (WiFi.status() != WL_CONNECTED) 
 {
  delay(200);
  Serial.print(".");
  i--; if(i<0) { i=50; Serial.println(); }
 }
 //-----success-------------------------------------------------
 Serial.print("\nConnected to WiFi! IP address is ");
 Serial.println(WiFi.localIP());
}

//_______process incoming message_______________________________
void callback(char* topic, byte* payload, unsigned int length)
{
 if(strcmp(topic, TOPIC_SET)==0) 
 { //----set topic received-------------------------------------
  if(length==1)
  {//....payload is one character: check it.....................
   if(payload[0]=='0') relayState=0;        // turn relay off
   if(payload[0]=='1') relayState=1;        // turn relay on
  }
  if(length==2)
  {//....payload has 2 character: is it -1 ?....................
   if(payload[0]=='-' && payload[1]=='1') relayState=1-relayState;
  }
  //-----set relay, send answer message, info to Serial---------
  digitalWrite(PIN_RELAY,relayState);       // update relay
  client.publish(TOPIC_RET, String(relayState).c_str());
  Serial.println("\nRelay state: "+String(relayState));
 }
}

//_______check for MQTT connection, if not: try to reconnect____
boolean reconnectMqtt() 
{
 //------when connected to broker, return-----------------------
 if(client.connected()) return true;
 Serial.print("MQTT: Not connected ==> try to reconnect: ");
 //------try to connect to mqtt broker--------------------------
 if(client.connect(clientId.c_str())) 
 {
  Serial.println(clientId+" connected.");
  //.....(re)subscribe topic....................................
  client.subscribe("relay/1/set");
  return true;
 }
 Serial.println("failed, client state rc="+String(client.state()));
 return false;
}

//_______setup Serial, digital IO, WLAN and MQTT client_________
void setup()
{
 //------Serial-------------------------------------------------
 Serial.begin(115200); Serial.println("\nsetup(): --Start--");
 //------set pin mode-------------------------------------------
 pinMode(PIN_LED, OUTPUT);                  // blue led
 digitalWrite(PIN_LED,LED_OFF);             // ...led off
 pinMode(PIN_RELAY, OUTPUT);                // relay output
 digitalWrite(PIN_RELAY,relayState);        // ...off
 //------setup WiFi + MQTT--------------------------------------
 setup_wifi();
 client.setServer(mqtt_server, 1883);
 client.setCallback(callback);
}

//_______main loop______________________________________________
void loop() 
{
 long now = millis();                       // ms since start
 //------check for mqtt connection------------------------------
 if (!client.connected())
 {//.....not connected to broker................................
  if(now - millis_lastTryToConnect > MQTT_RECONNECT_MS) 
  {//....it is time to try to reconnect to the Broker...........
   millis_lastTryToConnect=now;
   if(reconnectMqtt()) millis_lastTryToConnect=0;
  }
 }
 //------do something, if connected-----------------------------
 if (client.connected())
 {
  client.loop();                            // must be called!
  digitalWrite(PIN_LED,LED_ON);             // led on
  Serial.print("+");                        // connected to broker
 }
 else
 {
  digitalWrite(PIN_LED,LED_OFF);            // led off
  Serial.print(".");                        // not connected
 }
 //------do something, to show non blocking mode----------------
 delay(500);
}
