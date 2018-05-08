//_____D1_Ex45_test_is602.ino_________________180508-190508_____
// Test a i2c-spi-bridge SC18IS602B connected to D1 mini
// Hardware:
// D1mini  |  SC18IS602B-Pin
// --------+----------------
// D1=SCL  |   8=SCL
// D2=SDA  |   7=SDA
// 3V3     |  12=3V3
// GND     |   4=GND
// 
// Connections at IS602:
// A2=A1=A0=GND (pin 4-14-15-16)       7-bit i2c address 0x28
// MOSI -> MISO (pin 6-5)              send data, read them
// SS2 -> SS3   (pin 10-13)            GPIO: set SS2=out, SS3=in
// SS1          (pin 2)                GPIO: output
// Created by Karl Hartinger, May 08, 2018,
// Released into the public domain.
#include <Wire.h>                      // I2C library
int status;
int i2cAddress=0x28;
uint8_t byte1;

//**************************************************************
//    helper functions: i2c-access
//**************************************************************

//_____i2c: write 1 byte________________________________________
bool write8(byte reg, byte value) {
 Wire.beginTransmission(i2cAddress);
 Wire.write(reg);
 Wire.write(value);
 status=Wire.endTransmission();
 return true;
}

//_____i2c: read 1 byte_________________________________________
uint8_t read8(byte reg) {
 Wire.beginTransmission(i2cAddress);
 Wire.write(reg);
 status=Wire.endTransmission();
 Wire.requestFrom(i2cAddress, 1);
 uint8_t value=Wire.read();
 return value;
}

//==============================================================
void setup() {
 Serial.begin(115200); Serial.println();    // init Serial
 Serial.println("Test i2c-spi-bridge SC18IS602B @ D1 mini");
 Wire.begin();                              // 4=SDA, 5=SCL
 //-----configure SPI: MSByte first, mode 0, 1843kHz------------
 Serial.print("SPI config  : ");
 if(write8(0xF0, 0x00)) Serial.println("OK");
 else Serial.println("Error");
 //-----enable GPIO (0x0E=1110): ss3|ss2|ss1|ss0=no GPIO--------
 Serial.print("GPIO enable : ");
 if(write8(0xF6, 0x0E)) Serial.println("OK"); 
 else Serial.println("Error");
 //-----configure types of GPIO---------------------------------
 int in_=2, pushpull=1, nogpio=0;           // types of GPIO
 byte1=(in_<<6)+(pushpull<<4)+(pushpull<<2)+nogpio;
 Serial.print("GPIO config : ");
 if(write8(0xF7, byte1)) Serial.println("OK"); 
 else Serial.println("Error");
 //-----write GPIO output pins ss2 and ss1 (ss3=input, ss0=CS)--
 int ss1=0, ss2=1;                          // pin values
 Serial.print("Write GPIO  : ss1="); Serial.print(ss1);
 Serial.print(", ss2="); Serial.print(ss2);
 if(write8(0xF4, ss2*4+ss1*2)) Serial.println(" -> OK"); 
 else Serial.println(" -> Error");
 //-----read GPIO pin ss3---------------------------------------
 Serial.print("Read pin SS3: ");
 byte1=read8(0xF5);
 Serial.println(((byte1&8)>>3));
 //-----write 3 data bytes--------------------------------------
 Serial.println("Write data bytes...");
 Wire.beginTransmission(i2cAddress);
 Wire.write(0x01);
 Wire.write(0xAA);
 Wire.write(0x55);
 Wire.write(0xFF);
 status=Wire.endTransmission();
 //-----read 3 data bytes---------------------------------------
 Serial.print("Read data bytes: ");
 Wire.beginTransmission(i2cAddress);
 Wire.write(0x01);
 status=Wire.endTransmission();
 Wire.requestFrom(i2cAddress, 3);
 byte1=Wire.read();
 Serial.print("0x");Serial.print(byte1,16);
 byte1=Wire.read();
 Serial.print(" - 0x");Serial.print(byte1,16);
 byte1=Wire.read();
 Serial.print(" - 0x");Serial.println(byte1,16);
 Serial.println("Fertig!");
}

void loop() {
}
