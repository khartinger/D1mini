Display Analog In on OLED Shield and calculate input to another range (3..996 -> 0..255)

Hardware:
* WeMos D1 Mini
* trimmer (poti) at pins GND-A0-3V3
* OLED Shield: SSD1306, 64x48 pixel, I2C with SCL=D1=GPIO5, SDA=D2=GPIO4, OLED_RESET=D3=GPIO0


Uses Adafruit libs Adafruit_SSD1306-esp8266-64x48.zip and Adafruit-GFX-Library-1.1.5.zip

Text on OLED display:

    +--------+  
    |        |
    |   255  |  
    +--------+  
    --Sensor--  
     996  
   
