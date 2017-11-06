//_____D1_Ex40_SD_cardinfo.ino_____________________20171106_____
// Send infos about the micro SD card to Serial (9600Bd).
// During card access the blue LED is on :)
// Micro SD card agreements (for SD card library):
//   FAT16 or FAT32, 8.3 format filenames, NOT case-sensitive.
//
// Hardware: (1) WeMos D1 mini
//           (2) Micro SD shield
//               Pins used by SPI bus:
//               D5=CLK, D6=MISO, D7=MOSI, D8=CS, 3V3, GND
//
// This example code is in the public domain.
// Based on code by Limor Fried and Tom Igoe. See
//   https://github.com/esp8266/Arduino/blob/master/
//         libraries/SD/examples/CardInfo/CardInfo.ino

#include <SPI.h>                  // include SPI library
#include <SD.h>                   // include SD library
//-----variables using the SD utility library functions---------
Sd2Card   card;
SdVolume  volume;
SdFile    root;
const int chipSelect = D8;        // D1mini pin chip select SPI
const int pinBlueLED = D4;        // D1mini pin blue LED

void setup()
{
 Serial.begin(9600); while (!Serial) {;};   // wait for Serial
 Serial.println("\n\nPART 1: Initializing SD card...");
 //-----check for micro SD card---------------------------------
 digitalWrite(pinBlueLED, HIGH);  // LED on
 if (!card.init(SPI_HALF_SPEED, chipSelect)) 
 {
  Serial.println("Initialization failed. Is a card inserted?");
  digitalWrite(pinBlueLED, LOW);  // LED off
  return;
 }
 else
 {
  Serial.println("Wiring is correct and a card is present.");
 }
 //-----print type of card--------------------------------------
 Serial.print("Card type: ");
 switch (card.type()) 
 {
  case SD_CARD_TYPE_SD1:  Serial.println("SD1"); break;
  case SD_CARD_TYPE_SD2:  Serial.println("SD2"); break;
  case SD_CARD_TYPE_SDHC: Serial.println("SDHC"); break;
  default: Serial.println("Unknown");
 }
 
 //-----try to open volume/partition (should be FAT16 or FAT32)-
 Serial.println("\nPART 2: volume info");
 if (!volume.init(card)) 
 {
  Serial.println("Could not find FAT16/FAT32 partition.");
  Serial.println("Is card formatted?");
  digitalWrite(pinBlueLED, LOW);  // LED off
  return;
 }
 //-----print type and size of the first FAT-type volume--------
 uint8_t  temp8;
 uint32_t temp32;
 uint32_t volumesize;
 Serial.print("Volume type: FAT");
 Serial.println(volume.fatType(), DEC);     // decimal 16 or 32
 //.....number of blocks on micro SD card.......................
 Serial.println("Block size: 512 byte (fix)");
 temp32=volume.blocksPerCluster();          // num of blocks
 Serial.print("Number of blocks per cluster: ");
 Serial.println(temp32);
 volumesize=temp32;
 //.....number of clusters on micro SD card.....................
 temp32 = volume.clusterCount();           // num of clusters
 Serial.print("Number of clusters: ");
 Serial.println(temp32);                   // 1 block=512 bytes
 //.....volume size micro SD card...............................
 volumesize*=temp32;                       // * 512 = bytes
 volumesize/=2;                            // / 2   = KB
 Serial.print("Volume size (KBytes): ");   //
 Serial.println(volumesize);
 Serial.print("Volume size (MBytes): ");
 volumesize /= 1024;
 Serial.println(volumesize);
 Serial.print("Volume size (GBytes): ");
 volumesize /= 1024;
 Serial.println(volumesize);
 //-----show files on micro SD card-----------------------------
 Serial.println("\nPART 3: Files found on the micro SD card.");
 Serial.println("--filename.ext |---date---|--time--|size in bytes");
 Serial.print("  ");
 root.openRoot(volume);
 //-----list all files in the card with date and size-----------
 root.ls(LS_R | LS_DATE | LS_SIZE);
 digitalWrite(pinBlueLED, LOW);  // LED off
}

void loop()
{
 //.....nothing to do.....
}
