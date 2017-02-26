Accesspoint listens to Port 80 and increments counter on request or increments counter on falling edge of D5.
+ Push Button more then 3 sec resets counter
+ browser request 192.168.1.111/resetcounter resets counter
+ blue led indicates a http-request
HTTP-Answer   : counter value
OLED-Display  : counter value, client ip and signal strength
Serial monitor: config mode, log messages (19200Bd)
Config-Mode   : connect TX and RX while reset (3s -> reset)
 All server, oled and interrupt functions a placed in file 
 D1_Ex30_WifiAPCounterIntD5OledConf.h
 D1_ConfigServerEEPROM.h

Hardware:
* WeMos D1 Mini
* Push Button at D5
* OLED Shield: SSD1306, 64x48 pixel, I2C (SCL GPIO5, SDA GPIO4, OLED_RESET GPIO0)

Uses Adafruit libs Adafruit_SSD1306-esp8266-64x48.zip and Adafruit-GFX-Library-1.1.5.zip
