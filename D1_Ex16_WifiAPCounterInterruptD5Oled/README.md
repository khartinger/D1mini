Accesspoint listens to Port 80 and increments counter on request or increments counter on falling edge of D5.
+ Push Button more then 3 sec  resets counter
+ send 10.0.0.123/resetcounter resets counter
+ blue led indicates a http-request
HTTP-Answer   : counter value
OLED-Display  : counter value and client ip
Serial monitor: log messages (115200Bd)
All server functions a placed in header file   D1_Ex16_WifiAPCounterInterruptD5Oled.h

Hardware:
* WeMos D1 Mini
* Push Button at D5
* OLED Shield: SSD1306, 64x48 pixel, I2C (SCL GPIO5, SDA GPIO4, OLED_RESET GPIO0)

Uses Adafruit libs Adafruit_SSD1306-esp8266-64x48.zip and Adafruit-GFX-Library-1.1.5.zip
