# Di mini: Basic ESP8266 MQTT example
This sketch demonstrates the capabilities of the PubSubClient library in combination with a D1mini or a ESP8266 board.

Download the lib in the Arduino IDE (German Version):  
Sketch -> Bibliothek einbinden -> Bibliotheken verwalten... Eingabe von "PubSubClient" [Installieren]

This sketch connects to a MQTT server then:
* publishes "D1mini message #.." to the topic "Test1" every 5 seconds
* subscribes to the topic "Test1", printing out any message (String) it receives.

It will reconnect to the server if the connection is lost using a __blocking__ reconnect function.

__*Don't forget to change WiFi data to your network values!*__

You can see more here: 
https://github.com/knolleary/pubsubclient 
