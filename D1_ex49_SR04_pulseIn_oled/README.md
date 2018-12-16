# Di mini: Measure distance with ultrasonic sensor HC-SR04
Version 2018-11-16, file: `D1_Ex49_SR04_pulseIn_oled.ino`   
[German version](./LIESMICH.md "German version")   

The measured distance in cm is displayed on 0.66" OLED.   
![D1mini with HC04 sensor](./images/D1_SR04_1.png "D1 mini with HC04 sensor")   
_Figure 1: D1mini with adapter and und ultrasonic sensor HC-SR04_ 

## Hardware
1.  WeMos D1 mini   
2.  Self made ProtoBoard SR04 adapter with ultrasonic sensor HC-SR04
3.  OLED shield 0.66"    

![D1 SR04-adapter circuit](./images/D1_HC-SR04_Adapter_circuit1.png "Circuit D1mini with HC04 sensor")   
_Figure 2: Circuit D1 mini adapter for ultrasonic sensor HC-SR04_ 

![D1 Component side HC-SR04 adapter](./images/D1_SR04_comp1.png "Component side HC-SR04 adapter")   
_Figure 3: Component side HC-SR04 adapter_ 

![D1 Solder side HC-SR04 adapter](./images/D1_SR04_solder1.png "Solder side HC-SR04 adapter")   
_Figure 4: Solder side HC-SR04 adapter_ 

## Software
For displaying text on OLED class `Screen1` is used.   
(See directory `src`).   
