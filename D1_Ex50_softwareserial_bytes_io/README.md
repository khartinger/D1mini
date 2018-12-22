# D1 mini: Software Serial - Demo 1
Version 2018-11-01, File: `D1_Ex50_softwareserial_io.ino`   
[Deutsche Version](./LIESMICH.md "Deutsche Version")   

This program reads characters (bytes) from SoftwareSerial (9600 Bd, D6=Rx, D5=Tx), converts them to upper and sends them back (echo).   
Received bytes are also shown on (hardware) Serial.   
Blue LED blinks with 2Hz to demonstrate main loop is working.  

## Hardware
1. WeMos D1 mini   
2. PC with RS232-3V3-Converter and Terminalsoftware   
   Connect D1mini D5 (=Tx) with RxD, D6 (=Rx) with TxD, GND-GND and 3V3-3V3.   

__Important__: You __MUST__ use 3.3V for D1 mini pins!!!!   

## Software
Uses library `#include <SoftwareSerial.h>`
