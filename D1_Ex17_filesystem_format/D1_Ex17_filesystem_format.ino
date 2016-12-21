//_____D1_Ex17_filesystem_format___________________20161221_____
//Create a file system on the D1 mini. Has only to be done once!
//For SPIFFS documentation see
//https://github.com/esp8266/Arduino/blob/master/doc/filesystem.md
#include "FS.h"

//_____setup routine____________________________________________
void setup(void){
 bool ok=true;
 Serial.begin(9600);
 Serial.println("\nFormat file system SPIFFS (SPI Flash File System)");
 Serial.print("Please wait about 30 secs to 70 secs... ");
 ok = SPIFFS.format();
 if(!ok)
  Serial.println("=> ERROR while format()  :(");
 else
  Serial.println("=> SPIFFS formatted :)");
}

//_____main loop________________________________________________
void loop(void){
 //...nothing to do...
}
