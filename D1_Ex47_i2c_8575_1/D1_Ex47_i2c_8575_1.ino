//_____D1_Ex46_i2c_8574_1.ino_________________170114-180812_____
// Connect a 16bit PCF8575 I2C-IO-Expander
// to a D1mini (7bit-address 0x20). 
// Function: Running light and alternate flashing of IO-pins.
// Hardware: WeMos D1 Mini
//           PCF8575 @ i2c (SCL=D1, SDA=D2)
// Created by Karl Hartinger, August 12, 2018
// Last modified: -
// Released into the public domain.
#include <Wire.h>
#define DEBUG 1
#define PCF8575_ADDR (0x20)       // address of PCF8575
String s;
int i;

void setup() {
 if(DEBUG) { Serial.begin(115200); Serial.println(); }
 Wire.begin();
}

void loop() {
 //-----running light (lower 8 bit)-----------------------------
 for(i=0; i<8; i++)
 {
  Wire.beginTransmission(PCF8575_ADDR);
  Wire.write(1<<i);               // low byte
  Wire.write(0x00);               // high byte
  Wire.endTransmission();
  if(DEBUG) { s="0000"+String((1<<i),16)+" "; s=s.substring(s.length()-5); Serial.print(s); }
  delay(200);
 }
 if(DEBUG) Serial.println();
 //-----running light (higher 8 bit)----------------------------
 for(i=0; i<8; i++)
 {
  Wire.beginTransmission(PCF8575_ADDR);
  Wire.write(0x00);               // low byte
  Wire.write(1<<i);               // high byte
  Wire.endTransmission();
  if(DEBUG) { s="0000"+String((1<<(i+8)),16)+" "; s=s.substring(s.length()-5); Serial.print(s); }
  delay(200); 
 }
 if(DEBUG) Serial.println();
 for(i=0; i<2; i++)
 {
  //-----low byte 0xAA, high byte F0----------------------------
  Wire.beginTransmission(PCF8575_ADDR);
  Wire.write(0xAA);               // low byte
  Wire.write(0xF0);               // high byte
  Wire.endTransmission();
  if(DEBUG) Serial.println("F0 AA");
  delay(500);
  //-----low byte 0x55, high byte F0----------------------------
  Wire.beginTransmission(PCF8575_ADDR);
  Wire.write(0x55);               // low byte
  Wire.write(0x0F);               // high byte
  Wire.endTransmission();
  if(DEBUG) Serial.println("0F 55");
  delay(500);
 }
}

