//_____D1_Ex37_mqtt_taster1.h_________________170719-170719_____
#ifndef D1_EX37_MQTT_TASTER1_H
#define D1_EX37_MQTT_TASTER1_H
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

//.....Update these with values suitable for your network.......
const char* ssid = ".....";
const char* password = ".....";
const char* mqtt_server = "192.168.1.1";

WiFiClient espClient;
PubSubClient client(espClient);
long millis_lastConnected = 0;

#define MQTT_RECONNECT_MS         4000
#define TIMEOUT_WIFI_CONNECT_MS   8000 // wait for WLAN
#ifndef DEBUG1
 #define DEBUG1                   true // true=Serial output
#endif

//_____connect to the WiFi network______________________________
bool setup_wifi()
{
 if(WiFi.status()==WL_CONNECTED) return true;
 delay(10);
 if(DEBUG1) Serial.println("\nConnecting to "+String(ssid));
 WiFi.begin(ssid, password);
 //-----try to connect to WLAN (access point)-------------------
 int i=TIMEOUT_WIFI_CONNECT_MS/200;
 while((WiFi.status()!=WL_CONNECTED) && (i>0))
 {
  delay(200);
  i--;
  if(DEBUG1){Serial.print("."); if(i%50==0) Serial.println("");}
 }
 //-----connected to WLAN (access point)?-----------------------
 if(i<1)
 { //-----not connected to WLAN---------------------------------
  if(DEBUG1) Serial.println("No connection - time-out!");
  return false;
 }
 //-----success WiFi new connection/reconnect-------------------
 if(DEBUG1)Serial.println("\nConnected! IP address is "+WiFi.localIP().toString());
 return true;
}

//_____check for connect, if not: try to reconnect______________
boolean reconnect() 
{
 //-----when connected, return----------------------------------
 if(client.connected()) return true;
 //-----WiFi connected?-----------------------------------------
 if(!setup_wifi()) return false;
 //-----WiFi yes, mqtt no---------------------------------------
 if(DEBUG1)Serial.println("MQTT: Not connected - reconnect...");
 //-----Create a random client ID-------------------------------
 randomSeed(micros());            // start random numbers
 String clientId = "D1mini_Client-";
 clientId += String(random(0xffff), HEX);
 //-----Try to connect------------------------------------------
 if(client.connect(clientId.c_str())) 
 {
  if(DEBUG1) Serial.println(clientId+" connected.");
  //-----Once connected, publish an announcement----------------
  client.publish("button", "0");
  //.....and resubscribe.......................................
  client.subscribe("counter");
  return true;
 }
 if(DEBUG1)Serial.println("failed, client state rc="+String(client.state()));
 return false;
}

//_____is mqtt connection ok? (no: reconnect)___________________
bool isConnected()
{
 long now = millis();
 //-----check for mqtt connection-------------------------------
 if (!client.connected())
 {
  if (now - millis_lastConnected > MQTT_RECONNECT_MS) 
  {
   millis_lastConnected=now;
   if(reconnect()) millis_lastConnected=0;
  }
 }
 //-----if connected to broker, do loop function----------------
 if (client.connected())
 {
  client.loop();
  return true;
 }
 return false;
}
#endif

