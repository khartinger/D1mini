# D1 mini: Send a SMS by pressing a button
Version 2018-12-15, File: `D1_Ex52_sws_sms_send1.ino`   
[Deutsche Version](./LIESMICH.md "Deutsche Version")   

Press the Button D3 to send a SMS using the module "SIM800C GSM GPRS module STM32". 

## Hardware
1. WeMos D1 mini   
2. Battery Shield for WEMOS D1 mini with a small rechargeable battery HM04S (3,7V 350mAh 1,3Wh)   
3. Selfmade SIM800C 9pol ProtoBoard shield for "SIM800C GSM GPRS module STM32"   
4. 1-Button Shield   

![D1 SIM800C_STM32a](./images/D1_SIM800C_STM32a.png "D1mini mit SIM800C 9pol ProtoBoard Shield")   
_Figure 1: D1mini with battery shield, 9pol ProtoBoard shield and 1-Button Shield. On the left: 3,3V-RS232-Modul_ 

###  Special features of the hardware structure  
* The power supply of the SIM module is done by a special Adapter, because the D1 mini is not able to deliver sufficient (peak) energy.   
* The connection of the sim module is done by a self made SIM800C 9pol ProtoBoard Shield and software serial (D5=TX, D6=RX)   
* The connection to a PC is done by TX/RX-Pins and a 3.3V-RS232-Converter.   

While programming and testing this can also be done by using the USB-connector of the Aduino-IDE.   

## Prepare the SIM module
* Insert a micro SIM card in the SIM module. (For Austria e.g. a Pre-Paid-SIM from Drei or B.free)   
* Check, if the module recognises the sim card by query the SIM card number:   
`AT+CCID`   
* List the provider:   
`AT+COPS=?`   
* Check, if the card is registered to a network by   
`AT+COPS?` (without equal sign)   

## Control the SIM module
The red LED of the SIM module indicates the state:   
* Blinking at short intervals indicates, that the module is booting or trying to log in to a provider network.
* A flashing LED every 3 seconds indicates, that the module is ready to send or receive SMS.   
If the LED begins to blink in short intervals while sending a SMS, this indicates, that the module boots again. Perhaps  the voltage supply is too weak.

The software control of the SIM module is done by AT commands.   
| Command | Meaning |   
| -----  | ----- |   
| `ATE1` | Force sending back commands (echo). Answer should be "OK". |    
|`AT+CMGF=1` | Set text format. |    
|`AT+CPMS="ME","ME","ME"` | Define memory location for SMS (ME=Modul). |    
|`AT+CNMI=2,1,2,1,0` | Info, when a SMS is received. |    
| `AT+CMGS="0680xxxxxxx"` | Send a SMS. After sending the command a greater than sign &gt; appears and module waits for the SMS text. <br>__Important__: Finish SMS text with &lt;Strg&gt;Z = 0x1A |   
|`AT+CMGR=21` | Read SMS at location 21. Result might be:<br>`AT+CMGR=21<cr>`<br>`+CMGR: "REC UNREAD","+43680xxxxxxx","","18/12/15,17:06:50+04"<cr><lf>`<br>`#led on#<cr><lf><cr><lf>OK<cr><lf>` |   

###__*Example of serial output at PC*__
```
2018-12-15 D1_Ex52_sws_sms_send1
Press D3 to send a SMS
-----Init Modem-----
len=11: ATE1

OK

len=16: AT+CMGF=1

OK

len=54: AT+CPMS="ME","ME","ME"

+CPMS: 5,50,5,50,5,50

OK

len=24: AT+CNMI=2,1,2,1,0

OK

-----Modem OK-----
-----Button pressed!-----
len=74: 2018-12-15 D1_Ex52_sws_sms_send1
> Up-Time: 8298ms
> 
+CMGS: 54

OK

-----Sent finished-----
```

##Self made SIM800C 9pol ProtoBoard Shield
The SIM modul "SIM800C GSM GPRS module STM32" has some electrical specials:   
* Voltage supply 3.4V to 4.4V (NOT 3.3V and NOT 5V).   
Power supply from a 3.7 V lithium rechargeable battery should be possible according to the technical dossier of the manufacturer.
* Module needs a high current while sending a SMS (up to 2A).
* Serial port input: low -0.3..0.7V, high 2.1...3.1V   
Although manufacturer write "compatible to 3.3V and 5V systems" is this not correct. If the voltage on RX/TX pins is 3.3V, it sometimes comes to a boot process, especially if you send a SMS.   
You see the messages "Call Ready" and "SMS ready" at Serial and the red LED blinks in short intervals.   

It is a good idea, to use a voltage interface board, that can be build on a breadboard (hole matrix board).

![D1 9pol ProtoBoard Shield](./images/D1_SIM800C_STM32_Connect.png "D1mini SIM800C 9pol ProtoBoard Shield")   
_Figure 2: Circuit of the SIM800C 9pol ProtoBoard Shield_   

A 3.5V voltage generation with a 1.5V zener diode is just necessary, if you use a RS-232 connector that needs this. Otherwise you can omit it.
Instead of the USB-Connector you can use the 5V pin of the D1 mini, if voltage supply is done by a battery shield (this is stronger/better than D1 mini voltage supply)

![D1 9pol SIM interface boards](./images/D1_SIM800C_interfaceboards_comp.png "D1mini SIM800C D1 9pol interface boards") ![D1 9pol SIM interface boards](./images/D1_SIM800C_interfaceboards_solder.png "D1mini SIM800C D1 9pol interface boards (solder side)")      
_Figure 3: Prototypes of SIM800-interface boards (component- and solder side)_   
Note: part placement may be optimized ;)

"SIM800C 9pol ProtoBoard Shield" (left in figure 3): connector for hardware serial on the top (RX-TX-GND-3V3).   
Hole matrix board (right in figure 3): Voltage supply by a seperate USB connector. A micro controller (e.g. raspberry pi) may be connected using RX-TX-GND.

