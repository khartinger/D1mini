Access point 192.168.1.1 listens to Port 80 and counts the requests.  
HTTP-Answer: number of request  
OLED-Display: number of request and client ip  
All server functions a placed in header file D1_Ex14_WifiAPCounterOled.h

Hardware:
* WeMos D1 Mini
* OLED Shield: SSD1306, 64x48 pixel, I2C (SCL GPIO5, SDA GPIO4, OLED_RESET GPIO0)

Uses Adafruit libs Adafruit_SSD1306-esp8266-64x48.zip and Adafruit-GFX-Library-1.1.5.zip
