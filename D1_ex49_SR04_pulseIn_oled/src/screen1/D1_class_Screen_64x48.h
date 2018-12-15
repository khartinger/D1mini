//_____D1_class_Screen_64x48.h________________171229-180515_____
// The class Screen_64x48 contains basic OLED functions only for
// WeMos D1 mini OLED shield 0,66" 64*48 pixel.
// Special: char(158) = Euro instead of Pt (Pesetas) (158=9E)
// The code is strongly based on Adafruit libs
//   * _Adafruit_SSD1306-esp8266-64x48.zip and
//   * Adafruit-GFX-Library-1.1.5.zip
// To avoid problems with installed classes, Adafruit names in
// this class have a leading underline
// Use this class, if you have problems with the Adafruit
// classes especially after an update of the libraries.
//
#ifndef D1_CLASS_SCREEN_64x48_H
#define D1_CLASS_SCREEN_64x48_H
#include "Arduino.h"                   // boolean, ...
#include <pgmspace.h>                  // program memory
#include <Wire.h>                      // i2c

//**************************************************************
//    class Adafruit_SSD1306 (renamed to _Adafruit_SSD1306)
//**************************************************************

typedef volatile uint32_t PortReg;
typedef uint32_t PortMask;

#define BLACK                          0
#define WHITE                          1
#define INVERSE                        2

#define SSD1306_I2C_ADDRESS            0x3C //011110+SA0+RW-0x3C
#define SSD1306_64_48
#define SSD1306_LCDWIDTH               64
#define SSD1306_LCDHEIGHT              48

#define SSD1306_SETCONTRAST            0x81
#define SSD1306_DISPLAYALLON_RESUME    0xA4
#define SSD1306_DISPLAYALLON           0xA5
#define SSD1306_NORMALDISPLAY          0xA6
#define SSD1306_INVERTDISPLAY          0xA7
#define SSD1306_DISPLAYOFF             0xAE
#define SSD1306_DISPLAYON              0xAF
#define SSD1306_SETDISPLAYOFFSET       0xD3
#define SSD1306_SETCOMPINS             0xDA
#define SSD1306_SETVCOMDETECT          0xDB
#define SSD1306_SETDISPLAYCLOCKDIV     0xD5
#define SSD1306_SETPRECHARGE           0xD9
#define SSD1306_SETMULTIPLEX           0xA8

#define SSD1306_SETLOWCOLUMN           0x00
#define SSD1306_SETHIGHCOLUMN          0x10
#define SSD1306_SETSTARTLINE           0x40

#define SSD1306_MEMORYMODE             0x20
#define SSD1306_COLUMNADDR             0x21
#define SSD1306_PAGEADDR               0x22

#define SSD1306_COMSCANINC             0xC0
#define SSD1306_COMSCANDEC             0xC8

#define SSD1306_SEGREMAP               0xA0

#define SSD1306_CHARGEPUMP             0x8D
#define SSD1306_EXTERNALVCC            0x1
#define SSD1306_SWITCHCAPVCC           0x2

//-----Scrolling #defines---------------------------------------
#define SSD1306_ACTIVATE_SCROLL             0x2F
#define SSD1306_DEACTIVATE_SCROLL           0x2E
#define SSD1306_SET_VERTICAL_SCROLL_AREA    0xA3
#define SSD1306_RIGHT_HORIZONTAL_SCROLL     0x26
#define SSD1306_LEFT_HORIZONTAL_SCROLL      0x27
#define SSD1306_VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL  0x29
#define SSD1306_VERTICAL_AND_LEFT_HORIZONTAL_SCROLL   0x2A

//**************************************************************
//    structs from gfxfont.h
//**************************************************************

//_____Data stored PER GLYPH____________________________________
typedef struct {
 uint16_t bitmapOffset;      // Pointer into GFXfont->bitmap
 uint8_t  width, height;     // Bitmap dimensions in pixels
 uint8_t  xAdvance;          // Dist to advance cursor (x axis)
 int8_t   xOffset, yOffset;  // Dist from cursor to UL corner
} _GFXglyph;

//_____Data stored for FONT AS A WHOLE__________________________
typedef struct { 
 uint8_t   *bitmap;        // Glyph bitmaps, concatenated
 _GFXglyph *glyph;         // Glyph array
 uint8_t   first, last;    // ASCII extents
 uint8_t   yAdvance;       // Newline distance (y axis)
} _GFXfont;

//**************************************************************
//    basic class Adafruit_GFX (renamed to Adafruit_GFX0)
//**************************************************************

class _Adafruit_GFX : public Print {
 //-----constructor & co----------------------------------------
 public:
  _Adafruit_GFX(int16_t w, int16_t h); // Constructor
  //-----most important method: MUST be defined by the subclass-
  virtual void drawPixel(int16_t x,int16_t y,uint16_t color)=0;

  //-----TRANSACTION API / CORE DRAW API------------------------
  // MAY be overridden by subclass to provide device-specific
  // optimized code. Otherwise 'generic' versions are used.
  virtual void startWrite(void);
  virtual void writePixel(int16_t x, int16_t y, uint16_t color);
  virtual void writeFillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
  virtual void writeFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color);
  virtual void writeFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color);
  virtual void writeLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color);
  virtual void endWrite(void);

  //-----CONTROL API--------------------------------------------
  // MAY be overridden by subclass to provide device-specific
  // optimized code.  Otherwise 'generic' versions are used.
  virtual void setRotation(uint8_t r);
  virtual void invertDisplay(boolean i);

  //-----BASIC DRAW API-----------------------------------------
  // MAY be overridden by subclass to provide device-specific
  // optimized code.  Otherwise 'generic' versions are used.
  // It's good to implement those, even if using transaction API
  virtual void drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color);
  virtual void drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color);
  virtual void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
  virtual void fillScreen(uint16_t color);
  //.....Optional and probably not necessary to change..........
  virtual void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color);
  virtual void drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);

  //============================================================
  // These exist only with _Adafruit_GFX (no subclass overrides)
  void drawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);
  void drawCircleHelper(int16_t x0, int16_t y0, int16_t r, 
       uint8_t cornername, uint16_t color);
  void fillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);
  void  fillCircleHelper(int16_t x0, int16_t y0, int16_t r, 
        uint8_t cornername, int16_t delta, uint16_t color);
  void drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
      int16_t x2, int16_t y2, uint16_t color);
  void fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
      int16_t x2, int16_t y2, uint16_t color);
  void drawRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h,
      int16_t radius, uint16_t color);
  void fillRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h,
      int16_t radius, uint16_t color);
  void drawBitmap(int16_t x, int16_t y, const uint8_t bitmap[],
      int16_t w, int16_t h, uint16_t color);
  void drawBitmap(int16_t x, int16_t y, const uint8_t bitmap[],
      int16_t w, int16_t h, uint16_t color, uint16_t bg);
  void drawBitmap(int16_t x, int16_t y, uint8_t *bitmap,
      int16_t w, int16_t h, uint16_t color);
  void drawBitmap(int16_t x, int16_t y, uint8_t *bitmap,
      int16_t w, int16_t h, uint16_t color, uint16_t bg);
  void drawXBitmap(int16_t x, int16_t y, const uint8_t bitmap[],
      int16_t w, int16_t h, uint16_t color);
  void drawGrayscaleBitmap(int16_t x, int16_t y, 
      const uint8_t bitmap[], int16_t w, int16_t h);
  void drawGrayscaleBitmap(int16_t x, int16_t y, 
      uint8_t *bitmap, int16_t w, int16_t h);
  void drawGrayscaleBitmap(int16_t x, int16_t y,
      const uint8_t bitmap[], const uint8_t mask[],
      int16_t w, int16_t h);
  void drawGrayscaleBitmap(int16_t x, int16_t y,
      uint8_t *bitmap, uint8_t *mask, int16_t w, int16_t h);
  void drawRGBBitmap(int16_t x, int16_t y, const uint16_t bitmap[],
      int16_t w, int16_t h);
  void drawRGBBitmap(int16_t x, int16_t y, uint16_t *bitmap,
      int16_t w, int16_t h);
  void drawRGBBitmap(int16_t x, int16_t y,
      const uint16_t bitmap[], const uint8_t mask[],
      int16_t w, int16_t h);
  void drawRGBBitmap(int16_t x, int16_t y,
      uint16_t *bitmap, uint8_t *mask, int16_t w, int16_t h);
  void drawChar(int16_t x, int16_t y, unsigned char c, uint16_t color,
      uint16_t bg, uint8_t size);
  void setCursor(int16_t x, int16_t y);
  void setTextColor(uint16_t c);
  void setTextColor(uint16_t c, uint16_t bg);
  void setTextSize(uint8_t s);
  void  setTextWrap(boolean w);
  void setFont(const _GFXfont *f = NULL);
  void getTextBounds(char *string, int16_t x, int16_t y,
      int16_t *x1, int16_t *y1, uint16_t *w, uint16_t *h);
  void getTextBounds(const __FlashStringHelper *s, int16_t x, int16_t y,
      int16_t *x1, int16_t *y1, uint16_t *w, uint16_t *h);
  virtual size_t  write(uint8_t);
  //-----setter- and getter methods-----------------------------
  int16_t height(void) const;
  int16_t width(void) const;
  uint8_t getRotation(void) const;
  // get current cursor position (get rotation safe maximum values, using: width() for x, height() for y)
  int16_t getCursorX(void) const;
  int16_t getCursorY(void) const;

 protected:
  void charBounds(char c, int16_t *x, int16_t *y,
       int16_t *minx, int16_t *miny, int16_t *maxx, int16_t *maxy);

 //-----properties----------------------------------------------
 protected:
  //.....This is the 'raw' display w/h - never changes..........
  const int16_t WIDTH, HEIGHT;
  //.....Display width/height as modified by current rotation...
  int16_t  _width, _height;
  int16_t  cursor_x, cursor_y;
  uint16_t textcolor, textbgcolor;
  uint8_t  textsize;
  uint8_t  rotation;
  boolean  wrap;   // If set, 'wrap' text at right edge of display
  boolean  _cp437; // If set, use correct CP437 charset (default off)
  _GFXfont *gfxFont;
};

//**************************************************************
//    class _Adafruit_SSD1306 (renamed to _Adafruit_SSD1306)
//**************************************************************

class _Adafruit_SSD1306 : public _Adafruit_GFX {
 public:
  _Adafruit_SSD1306(int8_t SID, int8_t SCLK, int8_t DC, int8_t RST, int8_t CS);
  _Adafruit_SSD1306(int8_t DC, int8_t RST, int8_t CS);
  _Adafruit_SSD1306(int8_t RST = -1);

  void begin(uint8_t switchvcc = SSD1306_SWITCHCAPVCC, uint8_t i2caddr = SSD1306_I2C_ADDRESS, bool reset=true);
  void ssd1306_command(uint8_t c);

  void clearDisplay(void);
  void invertDisplay(uint8_t i);
  void display();

  void startscrollright(uint8_t start, uint8_t stop);
  void startscrollleft(uint8_t start, uint8_t stop);

  void startscrolldiagright(uint8_t start, uint8_t stop);
  void startscrolldiagleft(uint8_t start, uint8_t stop);
  void stopscroll(void);

  void dim(boolean dim);

  void drawPixel(int16_t x, int16_t y, uint16_t color);

  virtual void drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color);
  virtual void drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color);

 private:
  //int8_t _i2caddr, _vccstate, sid, sclk, dc, rst, cs;
  int8_t _i2caddr, _vccstate, rst;
  int8_t sid, sclk, dc, cs;
  inline void drawFastVLineInternal(int16_t x, int16_t y, int16_t h, uint16_t color) __attribute__((always_inline));
  inline void drawFastHLineInternal(int16_t x, int16_t y, int16_t w, uint16_t color) __attribute__((always_inline));
};

//**************************************************************
// special 5x8 font
//**************************************************************

const uint8_t fontKH_5x8Bitmaps[] PROGMEM = {
 0x00, 0x00, 0x00, 0x00, 0x00, // 0x20 ' '
 0x21, 0x08, 0x42, 0x00, 0x80, // 0x21 '!'	
 0x52, 0x94, 0x00, 0x00, 0x00, // 0x22 '"'
 0x52, 0xBE, 0xAF, 0xA9, 0x40, // 0x23 '#'
 0x23, 0xE8, 0xE2, 0xF8, 0x80, // 0x24 '$'
 0xC6, 0x44, 0x44, 0x4C, 0x60, // 0x25 '%'
 0x45, 0x28, 0x8A, 0xC9, 0xA0, // 0x26 '&'
 0x31, 0x88, 0x80, 0x00, 0x00, // 0x27 '''
 0x11, 0x10, 0x84, 0x10, 0x40, // 0x28 '('
 0x41, 0x04, 0x21, 0x11, 0x00, // 0x29 ')'
 0x25, 0x5D, 0xF7, 0x54, 0x80, // 0x2A '*' 
 0x01, 0x09, 0xF2, 0x10, 0x00, // 0x2B '+'
 0x00, 0x00, 0x03, 0x18, 0x88, // 0x2C ','
 0x00, 0x01, 0xF0, 0x00, 0x00, // 0x2D '-'
 0x00, 0x00, 0x00, 0x18, 0xC0, // 0x2E '.'
 0x00, 0x44, 0x44, 0x40, 0x00, // 0x2F '/'
 0x74, 0x67, 0x5C, 0xC5, 0xC0, // 0x30 '0'
 0x23, 0x08, 0x42, 0x11, 0xC0, // 0x21 '1'
 0x78, 0x42, 0xE8, 0x43, 0xE0, // 0x32 '2'
 0xF8, 0x44, 0x60, 0xC5, 0xC0, // 0x33 '3'
 0x11, 0x95, 0x2F, 0x88, 0x40, // 0x34 '4'
 0xFC, 0x3C, 0x10, 0xC5, 0xC0, // 0x35 '5'
 0x3A, 0x21, 0xE8, 0xC5, 0xC0, // 0x36 '6'
 0xF8, 0x42, 0x22, 0x22, 0x00, // 0x37 '7'
 0x74, 0x62, 0xE8, 0xC5, 0xC0, // 0x38 '8'
 0x74, 0x62, 0xF0, 0x8B, 0x80, // 0x39 '9'
 0x00, 0x08, 0x02, 0x00, 0x00, // 0x3A ':'
 0x00, 0x08, 0x02, 0x11, 0x08, // 0x3B ';'
 0x08, 0x88, 0x82, 0x08, 0x20, // 0x3C '<'
 0x00, 0x3E, 0x0F, 0x80, 0x00, // 0x3D '='
 0x41, 0x04, 0x11, 0x11, 0x00, // 0x3E '>'
 0x74, 0x42, 0x62, 0x00, 0x80, // 0x3F '?'
 0x74, 0x6B, 0x7B, 0x41, 0xE0, // 0x40 '@'
 0x22, 0xA3, 0x1F, 0xC6, 0x20, // 0x41 'A'
 0xF4, 0x63, 0xE8, 0xC7, 0xC0, // 0x42 'B'
 0x74, 0x61, 0x08, 0x45, 0xC0, // 0x43 'C'
 0xF4, 0x63, 0x18, 0xC7, 0xC0, // 0x44 'D'
 0xFC, 0x21, 0xE8, 0x43, 0xE0, // 0x45 'E'
 0xFC, 0x21, 0xE8, 0x42, 0x00, // 0x46 'F'
 0x7C, 0x61, 0x09, 0xC5, 0xE0, // 0x47 'G'
 0x8C, 0x63, 0xF8, 0xC6, 0x20, // 0x48 'H'
 0x71, 0x08, 0x42, 0x11, 0xC0, // 0x49 'I'
 0x38, 0x84, 0x21, 0x49, 0x80, // 0x4A 'J'
 0x8C, 0xA9, 0x8A, 0x4A, 0x20, // 0x4B 'K'
 0x84, 0x21, 0x08, 0x43, 0xE0, // 0x4C 'L'
 0x8E, 0xEB, 0x5A, 0xC6, 0x20, // 0x4D 'M'
 0x8C, 0x73, 0x59, 0xC6, 0x20, // 0x4E 'N'
 0x74, 0x63, 0x18, 0xC5, 0xC0, // 0x4F 'O'
 0xF4, 0x63, 0xE8, 0x42, 0x00, // 0x50 'P'
 0x74, 0x63, 0x1A, 0xC9, 0xA0, // 0x51 'Q'
 0xF4, 0x63, 0xEA, 0x4A, 0x20, // 0x52 'R'
 0x74, 0x60, 0xE0, 0xC5, 0xC0, // 0x53 'S'
 0xFD, 0x48, 0x42, 0x10, 0x80, // 0x54 'T'
 0x8C, 0x63, 0x18, 0xC5, 0xC0, // 0x55 'U'
 0x8C, 0x63, 0x18, 0xA8, 0x80, // 0x56 'V'
 0x8C, 0x63, 0x5A, 0xD5, 0x40, // 0x57 'W'
 0x8C, 0x54, 0x45, 0x46, 0x20, // 0x58 'X'
 0x8C, 0x54, 0x42, 0x10, 0x80, // 0x59 'Y'
 0xF8, 0x44, 0xE4, 0x43, 0xE0, // 0x5A 'Z'
 0x72, 0x10, 0x84, 0x21, 0xC0, // 0x5B '['
 0x04, 0x10, 0x41, 0x04, 0x00, // 0x5C '\'
 0x70, 0x84, 0x21, 0x09, 0xC0, // 0x5D ']'
 0x22, 0xA2, 0x00, 0x00, 0x00, // 0x5E '^'
 0x00, 0x00, 0x00, 0x03, 0xE0, // 0x5F '_'
 0x63, 0x08, 0x20, 0x00, 0x00, // 0x60 '`'
 0x00, 0x18, 0x27, 0x49, 0xE0, // 0x61 'a'
 0x84, 0x2D, 0x98, 0xE6, 0xC0, // 0x62 'b'
 0x00, 0x1D, 0x18, 0x45, 0xC0, // 0x63 'c'
 0x08, 0x5B, 0x38, 0xCD, 0xA0, // 0x64 'd'
 0x00, 0x1D, 0x1F, 0xC1, 0xC0, // 0x65 'e'
 0x11, 0x48, 0xE2, 0x10, 0x80, // 0x66 'f'
 0x00, 0x1D, 0x39, 0xB4, 0x2E, // 0x67 'g'
 0x84, 0x2D, 0x98, 0xC6, 0x20, // 0x68 'h'
 0x20, 0x18, 0x42, 0x11, 0xC0, // 0x69 'i'
 0x10, 0x04, 0x21, 0x49, 0x80, // 0x6A 'j'
 0x84, 0x25, 0x4C, 0x52, 0x40, // 0x6B 'k'
 0x61, 0x08, 0x42, 0x11, 0xC0, // 0x6C 'l'
 0x00, 0x35, 0x5A, 0xD6, 0xA0, // 0x6D 'm'
 0x00, 0x2D, 0x98, 0xC6, 0x20, // 0x6E 'n'
 0x00, 0x1D, 0x18, 0xC5, 0xC0, // 0x6F 'o'
 0x00, 0x2D, 0x9C, 0xDA, 0x10, // 0x70 'p'
 0x00, 0x1B, 0x39, 0xB4, 0x21, // 0x71 'q'
 0x00, 0x2D, 0x98, 0x42, 0x00, // 0x72 'r'
 0x00, 0x1F, 0x07, 0x07, 0xC0, // 0x73 's'
 0x21, 0x3E, 0x42, 0x14, 0x40, // 0x74 't'
 0x00, 0x23, 0x18, 0xCD, 0xA0, // 0x75 'u'
 0x00, 0x23, 0x18, 0xA8, 0x80, // 0x76 'v'
 0x00, 0x23, 0x1A, 0xD5, 0x40, // 0x77 'w'
 0x00, 0x22, 0xA2, 0x2A, 0x20, // 0x78 'x'
 0x00, 0x23, 0x17, 0x86, 0x2E, // 0x79 'y'
 0x00, 0x3E, 0x22, 0x23, 0xE0, // 0x7A 'z'
 0x11, 0x08, 0x82, 0x10, 0x40, // 0x7B '{'   7B left curly bracket
 0x21, 0x08, 0x02, 0x10, 0x80, // 0x7C '|'   7C vertical line
 0x41, 0x08, 0x22, 0x11, 0x00, // 0x7D '}'   7D right curly bracket
 0x45, 0x44, 0x00, 0x00, 0x00, // 0x7E '~'   7e tilde
 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // 0x7F = 127 7f <control>
 0x74, 0x61, 0x08, 0x45, 0xC4, // 0x80 C,
 0x50, 0x23, 0x18, 0xCD, 0xA0, // 0x81 = 129  c3bc u with diaeresis
 0x18, 0x1D, 0x1F, 0xC1, 0xE0, // 0x82 = 130
 0xF8, 0x18, 0x27, 0x49, 0xE0, // 0x83 = 131
 0x50, 0x18, 0x27, 0x49, 0xE0, // 0x84 = 132  c3a4 a with diaeresis
 0xC0, 0x18, 0x27, 0x49, 0xE0, // 0x85 = 133
 0x20, 0x18, 0x27, 0x49, 0xE0, // 0x86 = 134
 0x03, 0xF1, 0x87, 0x88, 0xC0, // 0x87 = 135
 0xF8, 0x1D, 0x1F, 0xC1, 0xE0, // 0x88 = 136
 0x88, 0x1D, 0x1F, 0xC1, 0xE0, // 0x89 = 137
 0xC0, 0x1D, 0x1F, 0xC1, 0xE0, // 0x8A = 138
 0x50, 0x18, 0x42, 0x11, 0xC0, // 0x8B = 139
 0x64, 0x80, 0xC2, 0x11, 0xC0, // 0x8C = 140
 0xC0, 0x18, 0x42, 0x11, 0xC0, // 0x8D = 141
 0x89, 0x15, 0x1F, 0xC6, 0x20, // 0x8E = 142  c384 A with diaeresis
 0x20, 0x08, 0xA8, 0xFE, 0x20, // 0x8F = 143
 0x30, 0x3D, 0x0E, 0x43, 0xC0, // 0x90 = 144
 0x00, 0x3C, 0x57, 0x51, 0xE0, // 0x91 = 145
 0x3A, 0xA5, 0xF9, 0x4A, 0x60, // 0x92 = 146
 0x22, 0x80, 0xE8, 0xC5, 0xC0, // 0x93 = 147
 0x50, 0x1D, 0x18, 0xC5, 0xC0, // 0x94 = 148  c3b6 o with diaeresis
 0x06, 0x00, 0xE8, 0xC5, 0xC0, // 0x95 = 149
 0x22, 0x81, 0x18, 0xCD, 0xA0, // 0x96 = 150
 0x06, 0x01, 0x18, 0xCD, 0xA0, // 0x97 = 151
 0x48, 0x12, 0x94, 0x9C, 0x2E, // 0x98 = 152
 0x8B, 0xA3, 0x18, 0xC5, 0xC0, // 0x99 = 153  c396 O with diaeresis
 0x88, 0x23, 0x18, 0xC5, 0xC0, // 0x9A = 154  c39c U with diaeresis
 0x21, 0x1F, 0x4A, 0x3C, 0x84, // 0x9B = 155  cent sign
 0x32, 0xD3, 0xC4, 0x23, 0xE0, // 0x9C = 156  pound sign
 0xDE, 0xDD, 0xF2, 0x7C, 0x84, // 0x9D = 157  yen sign
 0x32, 0x78, 0x8E, 0x24, 0xC0, // 0x9E = 158  Euro (!) 
 //0xE4, 0xA5, 0xC9, 0x5E, 0x52, // 0x9E = 158  Pt 
 0x19, 0x48, 0xE2, 0x12, 0x98, // 0x9F = 159  f
 0x18, 0x18, 0x27, 0x49, 0xE0, // 0xA0 = 160  
 0x18, 0x0C, 0x21, 0x08, 0xE0, // 0xA1 = 161
 0x00, 0xC0, 0xE8, 0xC5, 0xC0, // 0xA2 = 162
 0x00, 0xC1, 0x18, 0xCD, 0xA0, // 0xA3 = 163
 0x03, 0xC0, 0xE4, 0xA5, 0x20, // 0xA4 = 164
 0xF8, 0x33, 0xDB, 0xCE, 0x20, // 0xA5 = 165
 0x74, 0xA4, 0xF0, 0x7C, 0x00, // 0xA6 = 166  00A6 broken vertical bar
 0x74, 0x62, 0xE0, 0x7C, 0x00, // 0xA7 = 167
 0x20, 0x08, 0xC8, 0x45, 0xC0, // 0xA8 = 168
 0x00, 0x00, 0x0F, 0xC0, 0x00, // 0xA9 = 169
 0x00, 0x00, 0x0F, 0x84, 0x00, // 0xAA = 170
 0x84, 0x64, 0x45, 0xE4, 0x47, // 0xAB = 171  1/2
 0x84, 0x65, 0x55, 0xDC, 0x21, // 0xAC = 172  1/4
 0x21, 0x00, 0x42, 0x10, 0x80, // 0xAD = 173  inverted exclamation mark
 0x01, 0x55, 0x45, 0x14, 0x00, // 0xAE = 174  <<
 0x05, 0x14, 0x55, 0x50, 0x00, // 0xAF = 175  >>
 0xA8, 0x14, 0x0A, 0x81, 0x40, // 0xB0 = 176  25% block (was missing)
 0x55, 0x55, 0x55, 0x55, 0x55, // 0xB1 = 177  50% block
 0xFD, 0x7F, 0x5F, 0xD7, 0xF5, // 0xB2 = 178  75% block
 0x10, 0x84, 0x21, 0x08, 0x42, // 0xB3 = 179   |
 0x10, 0x84, 0x2F, 0x08, 0x42, // 0xB4 = 180  -|
 0x10, 0xBC, 0x2F, 0x08, 0x42, // 0xB5 = 181  =|
 0x29, 0x4A, 0x5E, 0x94, 0xA5, // 0xB6 = 182  -||
 0x00, 0x00, 0x0F, 0x94, 0xA5, // 0xB7 = 183  -,,
 0x00, 0x3E, 0x1F, 0x84, 0x21, // 0xB8 = 184  =,
 0x29, 0x7A, 0x1E, 0x94, 0xA5, // 0xB9 = 185  =||
 0x29, 0x4A, 0x52, 0x94, 0xA5, // 0xBA = 186 
 0x00, 0x3E, 0x1E, 0x94, 0xA5, // 0xBB = 187
 0x29, 0x7A, 0x1F, 0x80, 0x00, // 0xBC = 188
 0x29, 0x4A, 0x5F, 0x80, 0x00, // 0xBD = 189
 0x10, 0xBC, 0x2F, 0x00, 0x00, // 0xBE = 190
 0x00, 0x00, 0x0F, 0x08, 0x42, // 0xBF = 191  -,
 0x10, 0x84, 0x21, 0x80, 0x00, // 0xC0 = 192  221F '- right angle
 0x10, 0x84, 0x2F, 0x80, 0x00, // 0xC1 = 193
 0x00, 0x00, 0x0F, 0x88, 0x42, // 0xC2 = 194
 0x10, 0x84, 0x21, 0x88, 0x42, // 0xC3 = 195
 0x00, 0x00, 0x0F, 0x80, 0x00, // 0xC4 = 196  c384 A with diaeresis
 0x10, 0x84, 0x2F, 0x88, 0x42, // 0xC5 = 197  +
 0x10, 0x86, 0x21, 0x88, 0x42, // 0xC6 = 198
 0x29, 0x4A, 0x52, 0x94, 0xA5, // 0xC7 = 199
 0x29, 0x4A, 0x43, 0x80, 0x00, // 0xC8 = 200  ''=
 0x00, 0x0E, 0x42, 0x94, 0xA5, // 0xC9 = 201
 0x29, 0x7A, 0x0F, 0x80, 0x00, // 0xCA = 202
 0x00, 0x3E, 0x0E, 0x94, 0xA5, // 0xCB = 203
 0x29, 0x4A, 0x42, 0x94, 0xA5, // 0xCC = 204
 0x00, 0x3E, 0x0F, 0x80, 0x00, // 0xCD = 205
 0x29, 0x7A, 0x0E, 0x94, 0xA5, // 0xCE = 206
 0x10, 0xBE, 0x0F, 0x80, 0x00, // 0xCF = 207
 0x29, 0x4A, 0x5F, 0x80, 0x00, // 0xD0 = 208
 0x00, 0x3E, 0x0F, 0x88, 0x42, // 0xD1 = 209
 0x00, 0x00, 0x0F, 0x94, 0xA5, // 0xD2 = 210
 0x29, 0x4A, 0x53, 0x80, 0x00, // 0xD3 = 211
 0x10, 0x86, 0x21, 0x80, 0x00, // 0xD4 = 212
 0x00, 0x06, 0x21, 0x88, 0x42, // 0xD5 = 213
 0x00, 0x00, 0x03, 0x94, 0xA5, // 0xD6 = 214
 0x29, 0x4A, 0x5F, 0x94, 0xA5, // 0xD7 = 215
 0x10, 0xBE, 0x2F, 0x88, 0x42, // 0xD8 = 216
 0x10, 0x84, 0x2F, 0x00, 0x00, // 0xD9 = 217
 0x00, 0x00, 0x01, 0x88, 0x42, // 0xDA = 218
 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // 0xDB = 219
 0x00, 0x00, 0x0F, 0xFF, 0xFF, // 0xDC = 220
 0xE7, 0x39, 0xCE, 0x73, 0x9C, // 0xDD = 221
 0x18, 0xC6, 0x31, 0x8C, 0x63, // 0xDE = 222
 0xFF, 0xFF, 0xF0, 0x00, 0x00, // 0xDF = 223
 0x00, 0x1B, 0x29, 0x49, 0xA0, // 0xE0 = 224  03B1 alpha
 0x03, 0xA3, 0x68, 0xC6, 0xD0, // 0xE1 = 225  c39f sharp s, beta
 0xFC, 0xE1, 0x08, 0x42, 0x00, // 0xE2 = 226  
 0x00, 0x3E, 0xA5, 0x2A, 0x60, // 0xE3 = 227 
 0xFC, 0x50, 0x44, 0x47, 0xE0, // 0xE4 = 228   
 0x00, 0x1F, 0x29, 0x49, 0x80, // 0xE5 = 229 
 0x00, 0x14, 0xA5, 0x29, 0xB8, // 0xE6 = 230  c2b5 micro sign
 0x00, 0x1F, 0x42, 0x11, 0x80, // 0xE7 = 231  
 0xF9, 0x1D, 0x5A, 0xB8, 0x9F, // 0xE8 = 232 
 0x22, 0xA3, 0xF8, 0xA8, 0x80, // 0xE9 = 233 
 0x22, 0xA3, 0x15, 0x2B, 0x60, // 0xEA = 234 
 0x32, 0x0C, 0xE8, 0xC5, 0xC0, // 0xEB = 235 
 0x00, 0x17, 0x5D, 0x00, 0x00, // 0xEC = 236  221E infinity
 0x0B, 0xA7, 0x5A, 0xE5, 0xD0, // 0xED = 237  
 0x74, 0x21, 0xE8, 0x41, 0xC0, // 0xEE = 238
 0x74, 0x63, 0x18, 0xC6, 0x20, // 0xEF = 239
 0x07, 0xC1, 0xF0, 0x7C, 0x00, // 0xF0 = 240  2261 identical
 0x21, 0x3E, 0x42, 0x03, 0xE0, // 0xF1 = 241  c2b1 plus-minus
 0x41, 0x04, 0x44, 0x03, 0xE0, // 0xF2 = 242  2265 >=
 0x11, 0x10, 0x41, 0x03, 0xE0, // 0xF3 = 243  2264 <=
 0x39, 0x48, 0x42, 0x10, 0x80, // 0xF4 = 244  2320 top half integral 
 0x21, 0x08, 0x42, 0x52, 0x9C, // 0xF5 = 245  2321 bottom half integral
 0x31, 0x81, 0xF0, 0x18, 0xC0, // 0xF6 = 246  c3b7 division sign
 0x07, 0x6E, 0x0E, 0xDC, 0x00, // 0xF7 = 247  2248 almost equal to
 0x32, 0x52, 0x60, 0x00, 0x00, // 0xF8 = 248    B0 degree
 0x00, 0x00, 0x63, 0x00, 0x00, // 0xF9 = 249       point
 0x00, 0x00, 0x03, 0x00, 0x00, // 0xFA = 250       point
 0x39, 0x08, 0x4A, 0x51, 0x84, // 0xFB = 251  221A square root
 0x72, 0x52, 0x94, 0x80, 0x00, // 0xFC = 252  207F superscript n
 0x32, 0x44, 0x47, 0x80, 0x00, // 0xFD = 253  00B2 superscript 2
 0x00, 0x1E, 0xF7, 0xBC, 0x00, // 0xFE = 254  25A0|25AA black square
 0x00, 0x00, 0x00, 0x00, 0x00, // 0xFF = 255       blank
 0x00, 0x00, 0x00, 0x00, 0x00  // 0xFF = 255
};

const _GFXglyph fontKH_5x8Glyphs[] PROGMEM = {
 {   0,  5, 8,  6,  0, 0 },   // 0x20 ' ' 20 (UTF-8) space
 {   5,  5, 8,  6,  0, 0 },   // 0x21 '!' 21 exclamation mark
 {  10,  5, 8,  6,  0, 0 },   // 0x22 '"' 22 quotation mark
 {  15,  5, 8,  6,  0, 0 },   // 0x23 '#' 23 number sign
 {  20,  5, 8,  6,  0, 0 },   // 0x24 '$' 24 dollar sign
 {  25,  5, 8,  6,  0, 0 },   // 0x25 '%'
 {  30,  5, 8,  6,  0, 0 },   // 0x26 '&'
 {  35,  5, 8,  6,  0, 0 },   // 0x27 '''
 {  40,  5, 8,  6,  0, 0 },   // 0x28 '('
 {  45,  5, 8,  6,  0, 0 },   // 0x29 ')'
 {  50,  5, 8,  6,  0, 0 },   // 0x2A '*'
 {  55,  5, 8,  6,  0, 0 },   // 0x2B '+'
 {  60,  5, 8,  6,  0, 0 },   // 0x2C ','
 {  65,  5, 8,  6,  0, 0 },   // 0x2D '-'
 {  70,  5, 8,  6,  0, 0 },   // 0x2E '.'
 {  75,  5, 8,  6,  0, 0 },   // 0x2F '/'
 {  80,  5, 8,  6,  0, 0 },   // 0x30 '0'
 {  85,  5, 8,  6,  0, 0 },   // 0x31 '1'
 {  90,  5, 8,  6,  0, 0 },   // 0x32 '2'
 {  95,  5, 8,  6,  0, 0 },   // 0x33 '3'
 { 100,  5, 8,  6,  0, 0 },   // 0x34 '4'
 { 105,  5, 8,  6,  0, 0 },   // 0x35 '5'
 { 110,  5, 8,  6,  0, 0 },   // 0x36 '6'
 { 115,  5, 8,  6,  0, 0 },   // 0x37 '7'
 { 120,  5, 8,  6,  0, 0 },   // 0x38 '8'
 { 125,  5, 8,  6,  0, 0 },   // 0x39 '9'
 { 130,  5, 8,  6,  0, 0 },   // 0x3A ':'
 { 135,  5, 8,  6,  0, 0 },   // 0x3B ';'
 { 140,  5, 8,  6,  0, 0 },   // 0x3C '<'
 { 145,  5, 8,  6,  0, 0 },   // 0x3D '='
 { 150,  5, 8,  6,  0, 0 },   // 0x3E '>'
 { 155,  5, 8,  6,  0, 0 },   // 0x3F '?'
 { 160,  5, 8,  6,  0, 0 },   // 0x40 '@'
 { 165,  5, 8,  6,  0, 0 },   // 0x41 'A'
 { 170,  5, 8,  6,  0, 0 },   // 0x42 'B'
 { 175,  5, 8,  6,  0, 0 },   // 0x43 'C'
 { 180,  5, 8,  6,  0, 0 },   // 0x44 'D'
 { 185,  5, 8,  6,  0, 0 },   // 0x45 'E'
 { 190,  5, 8,  6,  0, 0 },   // 0x46 'F'
 { 195,  5, 8,  6,  0, 0 },   // 0x47 'G'
 { 200,  5, 8,  6,  0, 0 },   // 0x48 'H'
 { 205,  5, 8,  6,  0, 0 },   // 0x49 'I'
 { 210,  5, 8,  6,  0, 0 },   // 0x4A 'J'
 { 215,  5, 8,  6,  0, 0 },   // 0x4B 'K'
 { 220,  5, 8,  6,  0, 0 },   // 0x4C 'L'
 { 225,  5, 8,  6,  0, 0 },   // 0x4D 'M'
 { 230,  5, 8,  6,  0, 0 },   // 0x4E 'N'
 { 235,  5, 8,  6,  0, 0 },   // 0x4F 'O'
 { 240,  5, 8,  6,  0, 0 },   // 0x50 'P'
 { 245,  5, 8,  6,  0, 0 },   // 0x51 'Q'
 { 250,  5, 8,  6,  0, 0 },   // 0x52 'R'
 { 255,  5, 8,  6,  0, 0 },   // 0x53 'S'
 { 260,  5, 8,  6,  0, 0 },   // 0x54 'T'
 { 265,  5, 8,  6,  0, 0 },   // 0x55 'U'
 { 270,  5, 8,  6,  0, 0 },   // 0x56 'V'
 { 275,  5, 8,  6,  0, 0 },   // 0x57 'W'
 { 280,  5, 8,  6,  0, 0 },   // 0x58 'X'
 { 285,  5, 8,  6,  0, 0 },   // 0x59 'Y'
 { 290,  5, 8,  6,  0, 0 },   // 0x5A 'Z'
 { 295,  5, 8,  6,  0, 0 },   // 0x5B '['
 { 300,  5, 8,  6,  0, 0 },   // 0x5C '\'
 { 305,  5, 8,  6,  0, 0 },   // 0x5D ']'
 { 310,  5, 8,  6,  0, 0 },   // 0x5E '^'
 { 315,  5, 8,  6,  0, 0 },   // 0x5F '_'
 { 320,  5, 8,  6,  0, 0 },   // 0x60 '`'
 { 325,  5, 8,  6,  0, 0 },   // 0x61 'a'
 { 330,  5, 8,  6,  0, 0 },   // 0x62 'b'
 { 335,  5, 8,  6,  0, 0 },   // 0x63 'c'
 { 340,  5, 8,  6,  0, 0 },   // 0x64 'd'
 { 345,  5, 8,  6,  0, 0 },   // 0x65 'e'
 { 350,  5, 8,  6,  0, 0 },   // 0x66 'f'
 { 355,  5, 8,  6,  0, 0 },   // 0x67 'g'
 { 360,  5, 8,  6,  0, 0 },   // 0x68 'h'
 { 365,  5, 8,  6,  0, 0 },   // 0x69 'i'
 { 370,  5, 8,  6,  0, 0 },   // 0x6A 'j'
 { 375,  5, 8,  6,  0, 0 },   // 0x6B 'k'
 { 380,  5, 8,  6,  0, 0 },   // 0x6C 'l'
 { 385,  5, 8,  6,  0, 0 },   // 0x6D 'm'
 { 390,  5, 8,  6,  0, 0 },   // 0x6E 'n'
 { 395,  5, 8,  6,  0, 0 },   // 0x6F 'o'
 { 400,  5, 8,  6,  0, 0 },   // 0x70 'p'
 { 405,  5, 8,  6,  0, 0 },   // 0x71 'q'
 { 410,  5, 8,  6,  0, 0 },   // 0x72 'r'
 { 415,  5, 8,  6,  0, 0 },   // 0x73 's'
 { 420,  5, 8,  6,  0, 0 },   // 0x74 't'
 { 425,  5, 8,  6,  0, 0 },   // 0x75 'u'
 { 430,  5, 8,  6,  0, 0 },   // 0x76 'v'
 { 435,  5, 8,  6,  0, 0 },   // 0x77 'w'
 { 440,  5, 8,  6,  0, 0 },   // 0x78 'x'
 { 445,  5, 8,  6,  0, 0 },   // 0x79 'y'
 { 450,  5, 8,  6,  0, 0 },   // 0x7A 'z'
 { 455,  5, 8,  6,  0, 0 },   // 0x7B '{'
 { 460,  5, 8,  6,  0, 0 },   // 0x7C '|'
 { 465,  5, 8,  6,  0, 0 },   // 0x7D '}'
 { 470,  5, 8,  6,  0, 0 },   // 0x7E '~'
 { 475,  5, 8,  6,  0, 0 },   // 0x7F '' 
 { 480,  5, 8,  6,  0, 0 },   // 0x80 = 128 
 { 485,  5, 8,  6,  0, 0 },   // 0x81 = 129
 { 490,  5, 8,  6,  0, 0 },   // 0x82 = 130 
 { 495,  5, 8,  6,  0, 0 },   // 0x83 = 131  
 { 500,  5, 8,  6,  0, 0 },   // 0x84 = 132 
 { 505,  5, 8,  6,  0, 0 },   // 0x85 = 133
 { 510,  5, 8,  6,  0, 0 },   // 0x86 = 134 
 { 515,  5, 8,  6,  0, 0 },   // 0x87 = 135
 { 520,  5, 8,  6,  0, 0 },   // 0x88 = 136
 { 525,  5, 8,  6,  0, 0 },   // 0x89 = 137
 { 530,  5, 8,  6,  0, 0 },   // 0x8A = 138
 { 535,  5, 8,  6,  0, 0 },   // 0x8B = 139
 { 540,  5, 8,  6,  0, 0 },   // 0x8C = 140 
 { 545,  5, 8,  6,  0, 0 },   // 0x8D = 141
 { 550,  5, 8,  6,  0, 0 },   // 0x8E = 142
 { 555,  5, 8,  6,  0, 0 },   // 0x8F = 143
 { 560,  5, 8,  6,  0, 0 },   // 0x90 = 144 
 { 565,  5, 8,  6,  0, 0 },   // 0x91 = 145
 { 570,  5, 8,  6,  0, 0 },   // 0x92 = 146
 { 575,  5, 8,  6,  0, 0 },   // 0x93 = 147
 { 580,  5, 8,  6,  0, 0 },   // 0x94 = 148
 { 585,  5, 8,  6,  0, 0 },   // 0x95 = 149
 { 590,  5, 8,  6,  0, 0 },   // 0x96 = 150
 { 595,  5, 8,  6,  0, 0 },   // 0x97 = 151
 { 600,  5, 8,  6,  0, 0 },   // 0x98 = 152
 { 605,  5, 8,  6,  0, 0 },   // 0x99 = 153
 { 610,  5, 8,  6,  0, 0 },   // 0x9A = 154
 { 615,  5, 8,  6,  0, 0 },   // 0x9B = 155
 { 620,  5, 8,  6,  0, 0 },   // 0x9C = 156
 { 625,  5, 8,  6,  0, 0 },   // 0x9D = 157
 { 630,  5, 8,  6,  0, 0 },   // 0x9E = 158
 { 635,  5, 8,  6,  0, 0 },   // 0x9F = 159
 { 640,  5, 8,  6,  0, 0 },   // 0xA0 = 160
 { 645,  5, 8,  6,  0, 0 },   // 0xA1 = 161
 { 650,  5, 8,  6,  0, 0 },   // 0xA2 = 162
 { 655,  5, 8,  6,  0, 0 },   // 0xA3 = 163
 { 660,  5, 8,  6,  0, 0 },   // 0xA4 = 164
 { 665,  5, 8,  6,  0, 0 },   // 0xA5 = 165
 { 670,  5, 8,  6,  0, 0 },   // 0xA6 = 166
 { 675,  5, 8,  6,  0, 0 },   // 0xA7 = 167
 { 680,  5, 8,  6,  0, 0 },   // 0xA8 = 168
 { 685,  5, 8,  6,  0, 0 },   // 0xA9 = 169
 { 690,  5, 8,  6,  0, 0 },   // 0xAA = 170
 { 695,  5, 8,  6,  0, 0 },   // 0xAB = 171
 { 700,  5, 8,  6,  0, 0 },   // 0xAC = 172
 { 705,  5, 8,  6,  0, 0 },   // 0xAD = 173
 { 710,  5, 8,  6,  0, 0 },   // 0xAE = 174  <<
 { 715,  5, 8,  6,  0, 0 },   // 0xAF = 175  >>
 { 720,  5, 8,  6,  0, 0 },   // 0xB0 = 176  25% block
 { 725,  5, 8,  6,  0, 0 },   // 0xB1 = 177  50% block
 { 730,  5, 8,  6,  0, 0 },   // 0xB2 = 178  75% block
 { 735,  5, 8,  6,  0, 0 },   // 0xB3 = 179
 { 740,  5, 8,  6,  0, 0 },   // 0xB4 = 180
 { 745,  5, 8,  6,  0, 0 },   // 0xB5 ' ' 
 { 750,  5, 8,  6,  0, 0 },   // 0xB6 ' ' 
 { 755,  5, 8,  6,  0, 0 },   // 0xB7 ' ' 
 { 760,  5, 8,  6,  0, 0 },   // 0xB8 ' ' 
 { 765,  5, 8,  6,  0, 0 },   // 0xB9 ' ' 
 { 770,  5, 8,  6,  0, 0 },   // 0xBA ' ' 
 { 775,  5, 8,  6,  0, 0 },   // 0xBB ' ' 
 { 780,  5, 8,  6,  0, 0 },   // 0xBC ' ' 
 { 785,  5, 8,  6,  0, 0 },   // 0xBD ' ' 
 { 790,  5, 8,  6,  0, 0 },   // 0xBE ' ' 
 { 795,  5, 8,  6,  0, 0 },   // 0xBF ' ' 
 { 800,  5, 8,  6,  0, 0 },   // 0xC0 ' ' 
 { 805,  5, 8,  6,  0, 0 },   // 0xC1 ' ' 
 { 810,  5, 8,  6,  0, 0 },   // 0xC2 ' ' 
 { 815,  5, 8,  6,  0, 0 },   // 0xC3 ' ' 
 { 820,  5, 8,  6,  0, 0 },   // 0xC4 'Ae' c384 A with diaeresis
 { 825,  5, 8,  6,  0, 0 },   // 0xC5 ' ' 
 { 830,  5, 8,  6,  0, 0 },   // 0xC6 ' ' 
 { 835,  5, 8,  6,  0, 0 },   // 0xC7 ' ' 
 { 840,  5, 8,  6,  0, 0 },   // 0xC8 ' ' 
 { 845,  5, 8,  6,  0, 0 },   // 0xC9 ' ' 
 { 850,  5, 8,  6,  0, 0 },   // 0xCA ' ' 
 { 855,  5, 8,  6,  0, 0 },   // 0xCB ' ' 
 { 860,  5, 8,  6,  0, 0 },   // 0xCC ' ' 
 { 865,  5, 8,  6,  0, 0 },   // 0xCD ' ' 
 { 870,  5, 8,  6,  0, 0 },   // 0xCE ' ' 
 { 875,  5, 8,  6,  0, 0 },   // 0xCF ' ' 
 { 880,  5, 8,  6,  0, 0 },   // 0xD0 ' ' 
 { 885,  5, 8,  6,  0, 0 },   // 0xD1 ' ' 
 { 890,  5, 8,  6,  0, 0 },   // 0xD2 ' ' 
 { 895,  5, 8,  6,  0, 0 },   // 0xD3 ' ' 
 { 900,  5, 8,  6,  0, 0 },   // 0xD4 ' ' 
 { 905,  5, 8,  6,  0, 0 },   // 0xD5 ' ' 
 { 910,  5, 8,  6,  0, 0 },   // 0xD6 ' ' 
 { 915,  5, 8,  6,  0, 0 },   // 0xD7 ' ' 
 { 920,  5, 8,  6,  0, 0 },   // 0xD8 ' ' 
 { 925,  5, 8,  6,  0, 0 },   // 0xD9 ' ' 
 { 930,  5, 8,  6,  0, 0 },   // 0xDA ' ' 
 { 935,  5, 8,  6,  0, 0 },   // 0xDB ' ' 
 { 940,  5, 8,  6,  0, 0 },   // 0xDC ' ' 
 { 945,  5, 8,  6,  0, 0 },   // 0xDD ' ' 
 { 950,  5, 8,  6,  0, 0 },   // 0xDE ' ' 
 { 955,  5, 8,  6,  0, 0 },   // 0xDF ' ' 
 { 960,  5, 8,  6,  0, 0 },   // 0xE0 = 224  alpha
 { 965,  5, 8,  6,  0, 0 },   // 0xE1 = 225  beta, sharp s
 { 970,  5, 8,  6,  0, 0 },   // 0xE2 = 226
 { 975,  5, 8,  6,  0, 0 },   // 0xE3 = 227  pi
 { 980,  5, 8,  6,  0, 0 },   // 0xE4 ' ' 
 { 985,  5, 8,  6,  0, 0 },   // 0xE5 ' ' 
 { 990,  5, 8,  6,  0, 0 },   // 0xE6 ' ' 
 { 995,  5, 8,  6,  0, 0 },   // 0xE7 ' ' 
 {1000,  5, 8,  6,  0, 0 },   // 0xE8 ' ' 
 {1005,  5, 8,  6,  0, 0 },   // 0xE9 ' ' 
 {1010,  5, 8,  6,  0, 0 },   // 0xEA ' ' 
 {1015,  5, 8,  6,  0, 0 },   // 0xEB ' ' 
 {1020,  5, 8,  6,  0, 0 },   // 0xEC ' ' 
 {1025,  5, 8,  6,  0, 0 },   // 0xED ' ' 
 {1030,  5, 8,  6,  0, 0 },   // 0xEE ' ' 
 {1035,  5, 8,  6,  0, 0 },   // 0xEF ' ' 
 {1040,  5, 8,  6,  0, 0 },   // 0xF0 ' ' 
 {1045,  5, 8,  6,  0, 0 },   // 0xF1 ' ' 
 {1050,  5, 8,  6,  0, 0 },   // 0xF2 ' ' 
 {1055,  5, 8,  6,  0, 0 },   // 0xF3 ' ' 
 {1060,  5, 8,  6,  0, 0 },   // 0xF4 ' ' 
 {1065,  5, 8,  6,  0, 0 },   // 0xF5 ' ' 
 {1070,  5, 8,  6,  0, 0 },   // 0xF6 ' ' 
 {1075,  5, 8,  6,  0, 0 },   // 0xF7 ' ' 
 {1080,  5, 8,  6,  0, 0 },   // 0xF8 ' ' 
 {1085,  5, 8,  6,  0, 0 },   // 0xF9 ' ' 
 {1090,  5, 8,  6,  0, 0 },   // 0xFA ' ' 
 {1095,  5, 8,  6,  0, 0 },   // 0xFB ' ' 
 {1100,  5, 8,  6,  0, 0 },   // 0xFC ' ' 
 {1105,  5, 8,  6,  0, 0 },   // 0xFD ' ' 
 {1110,  5, 8,  6,  0, 0 },   // 0xFE ' ' 
 {1115,  5, 8,  6,  0, 0 },   // 0xFF ' ' 
 {1120,  5, 8,  6,  0, 0 } }; // 0xFF ' ' 
const _GFXfont fontKH_5x8 PROGMEM = {
  (uint8_t  *) fontKH_5x8Bitmaps,
  (_GFXglyph *)fontKH_5x8Glyphs,
  0x20, 0xFF, 8};

#endif
