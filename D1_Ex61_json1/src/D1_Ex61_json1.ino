//_____D1_Ex61_json1.ino_________________________khartinger_____
// This program shows how to use JSON data
// See https://arduinojson.org/v6/example/parser/
// Hardware: 
// (1) WeMos D1 mini (OR ESP32 D1 mini)
// Visual Studio Code with platform.IO: 
//   Add this line to platformio.ini:
//   lib_deps = bblanchon/ArduinoJson@^6.21.1
// Created by Karl Hartinger, April 10, 2023.
// Changes:
// 2023-04-10 New
// Released into the public domain.
#include <ArduinoJson.h>

//_______SETUP__________________________________________________
void setup() {
 //------Serial-------------------------------------------------
 Serial.begin(115200); while(!Serial) continue;
 Serial.println("\nsetup(): --Start--");
 //------Generate JSON string-----------------------------------
 StaticJsonDocument<200> doc;
 char json[] = "{\"name\":\"Linda\",\"age\":21,\"hobbies\":[\"h1\",\"h2\"], \"data\":[85,66,87]}";
 //------Deserialize the JSON document--------------------------
 DeserializationError error = deserializeJson(doc, json);
 //------Test if parsing succeeds-------------------------------
 if (error) {
  Serial.print(F("deserializeJson() failed: "));
  Serial.println(error.f_str());
  return;
 }
 //------Fetch values-------------------------------------------
 const char* name = doc["name"];
 int age = doc["age"];
 const char* hobby1 = doc["hobbies"][0];
 const char* hobby2 = doc["hobbies"][1];
 double data1 = doc["data"][0];
 double data2 = doc["data"][1];
 double data3 = doc["data"][2];
 //------Print values-------------------------------------------
 Serial.print("Name: "); Serial.println(name);
 Serial.print("Age: "); Serial.println(age);
 Serial.print("Hobby1: "); Serial.println(hobby1);
 Serial.print("Hobby2: "); Serial.println(hobby2);
 Serial.print("data1: "); Serial.println(data1);
 Serial.print("data2: "); Serial.println(data2);
 Serial.print("data3: "); Serial.println(data3);
 Serial.println("setup(): --Finished--\n");
}

//_______LOOP___________________________________________________
void loop() {
}