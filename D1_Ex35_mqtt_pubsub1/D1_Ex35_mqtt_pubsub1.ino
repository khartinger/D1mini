//_____D1_Ex35_mqtt_pubsub1.ino_______________170718-170718_____
// Basic ESP8266 MQTT example
// This sketch demonstrates the capabilities of the PubSubClient 
// library in combination with a D1mini or a ESP8266 board.
// Download the lib: Sketch – Bibliothek einbinden – Bibliotheken
//   verwalten... Eingabe von "PubSubClient" [Installieren]
//
// It connects to a MQTT server then:
//  - publishes "D1mini message #.." to the topic "Test1"
//    every 5 seconds
//  - subscribes to the topic "Test1", printing out any message
//    (String) it receives.
//
// It will reconnect to the server if the connection is lost
// using a blocking reconnect function.
//
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#define MESSAGE_MAXLEN       127

//.....Update these with values suitable for your network.......
const char* ssid = "..........";
const char* password = "..........";
const char* mqtt_server = "192.168.x.x";

WiFiClient espClient;
PubSubClient client(espClient);
long millis_lastMsg = 0;
char msg[1+MESSAGE_MAXLEN];
int value = 0;

//_____connect to the WiFi network______________________________
void setup_wifi()
{
 delay(10);
 randomSeed(micros());            // start random numbers
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
 Serial.print("\nConnected! IP address is ");
 Serial.println(WiFi.localIP());
}

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

//_____check for connect, loop until reconnected________________
void reconnect() 
{
 //-----Loop until reconnected----------------------------------
 while (!client.connected()) 
 {
  Serial.println("Attempting MQTT connection...");
  //-----Create a random client ID------------------------------
  String clientId = "D1mini_Client-";
  clientId += String(random(0xffff), HEX);
  //-----Attempt to connect-------------------------------------
  if (client.connect(clientId.c_str())) 
  {
   Serial.println(clientId+" connected.");
   //-----Once connected, publish an announcement---------------
   client.publish("Test1", "(Re)connect: Hello from D1mini :)");
   //.....and resubscribe.......................................
   client.subscribe("Test1");
  }
  else 
  {
   Serial.print("failed, client state rc=");
   Serial.print(client.state());
   Serial.println(" try again in 5 seconds");
   delay(5000);              // Wait 5 seconds before retrying
  }
 }
}

//_____setup Serial, WLAN and MQTT clients______________________
void setup() 
{
 Serial.begin(9600);
 setup_wifi();
 client.setServer(mqtt_server, 1883);
 client.setCallback(callback);
}

//_____main loop________________________________________________
void loop() 
{
 if (!client.connected()) reconnect();
 client.loop();
 long now = millis();
 if (now - millis_lastMsg > 5000) 
 {
  millis_lastMsg = now;
  value++;
  snprintf(msg, MESSAGE_MAXLEN, "D1mini message #%ld", value);
  Serial.println("Publish message: "+String(msg));
  client.publish("Test1", msg, true);       // true=retain
 }
}
