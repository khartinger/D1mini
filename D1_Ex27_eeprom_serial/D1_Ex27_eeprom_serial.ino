//_____D1_Ex27_eeprom_serial.ino___________________20170125_____
// This program demonstrates how to write bytes (text) from 
// Serial into a eeprom and read bytes from eeprom.
// Commands for reading and writing are written between {}
// -------------Examples for serial commands--------------------
// {W 01234567} write 01234567 to eeprom, starting at address 0
// {W2 Hallo}   write Hallo to eeprom, starting at address 2
// {R2 4}       read 4 Bytes from eeprom starting at address 2
// To test the limit checks the EEPROM_SIZE is set to 8 (bytes).
//
// Hardware: WeMos D1 mini (Serial at 19200 Bd)

#include "EEPROM.h"
#define EEPROM_SIZE   8

#define BUFFER_SIZE   15+EEPROM_SIZE
uint8_t buffer[BUFFER_SIZE];
int  ibuffer=-1;                  // index in buffer

//==============================================================
// functions for eeprom read/write
//==============================================================

//_____read a block from eeprom_________________________________
// uses: EEPROM_SIZE
// return: number of read bytes or -1|-2|-3 on error
size_t eeprom_read_block(uint8_t * data, uint32_t address, 
 size_t len){
 int i;
 //-----check input---------------------------------------------
 if(len==0)    return -1;
 if(len<0)     return -2;
 if(address<0) return -3;
 if((address+len)>EEPROM_SIZE)
 {
  len=EEPROM_SIZE-address;        // or return -4
 }
 //-----read bytes----------------------------------------------
 for(i=0; i<len; i++)
  data[i]=EEPROM.read(address+i);
 return len;
}

//_____write a block to eeprom__________________________________
// uses: EEPROM_SIZE
// return: number of written bytes or -1|-2|-3 on error
size_t eeprom_write_block(uint8_t * data, uint32_t address, 
 size_t len){
 int i;
 //-----check input---------------------------------------------
 if(len==0)    return -1;
 if(len<0)     return -2;
 if(address<0) return -3;
 if((address+len)>EEPROM_SIZE)
 {
  len=EEPROM_SIZE-address;        // or return -4
 }
 //-----write bytes---------------------------------------------
 for(i=0; i<len; i++) 
  EEPROM.write(address+i, data[i]);
 EEPROM.commit();
 return len;
}

//==============================================================
//  special functions for this example
//==============================================================

//_____show infos and read a block from eeprom__________________
// return: number of written bytes
size_t demo_eeprom_read_block(uint8_t * data, uint32_t address, 
 size_t len){
 int i;
 Serial.println("---------eeprom_read_block------------------");
 Serial.println("Address: " + String(address));
 Serial.println("Length : " + String(len));
 if((address+len)>EEPROM_SIZE)
 {
  len=EEPROM_SIZE-address;
  Serial.print("Block too large. Only ");
  Serial.print(len);
  Serial.println(" bytes read.");
 }
 //-----read data from eeprom-----------------------------------
 len=eeprom_read_block(data, address, len);
 return len;
}

//_____read a block from eeprom_________________________________
// return: number of written bytes
size_t demo_eeprom_write_block(uint8_t * data, uint32_t address, 
 size_t len){
 int i;
 Serial.println("---------eeprom_write_block-----------------");
 Serial.print  ("Text   : "); 
 for(int i=0; i<len; i++) Serial.print((char)data[i]);
 Serial.println();
 Serial.println("Address: " + String(address));
 Serial.println("Length : " + String(len));
 if((address+len)>EEPROM_SIZE)
 {
  len=EEPROM_SIZE-address;
  Serial.print("Block does not fit in EEPROM. Only ");
  Serial.print(len);
  Serial.println(" bytes written.");
 }
 //-----write data to eeprom------------------------------------
 len=eeprom_write_block(data, address, len);
 return len;
}

//_____get address from buffer__________________________________
// writes address to global variable address
// returns: length of address in bytes (-1 on error)
int getAddress(uint32_t *address)
{
 char numbuffer[12];              // to convert char to address
 char c2;
 int j;
 *address=0;
 //-----start address?------------------------------------------
 if(!isDigit(buffer[1]))
 {
  if(buffer[1]==' ') return 0;
  return -1;
 }
 //-----convert start address-----------------------------------
 j=0;
 while(isDigit(c2=buffer[j+1]))
 {
  if(j>10) return -1;
  numbuffer[j++]=c2;
 }
 if(c2!=' ') return -1;
 numbuffer[j]=0;
 *address=atoi(numbuffer);
 return j;
}
 
//_____get number of bytes to read from buffer__________________
int getReadLen(int istart)
{
 char numbuffer[11];              // to convert char to address
 int j;
 if(ibuffer-istart>10) return 0;
 for(j=0; j<ibuffer-istart; j++)
 {
  if(!isDigit(buffer[j+istart])) continue; //return 0;
  numbuffer[j]=buffer[j+istart];
 }
 numbuffer[j]=0;
 return(atoi(numbuffer));
}

//_____execute command in buffer________________________________
// return: number of bytes written or read
//         -1 wrong address
int doCommand(void)
{
 int i, len1;
 uint32_t address;
 //-----print command to serial---------------------------------
 //Serial.println("\nExecute command:");
 //for(int i=0; i<ibuffer; i++)
 // Serial.print((char) buffer[i]);
 //Serial.println();
 //-----write eeprom?-------------------------------------------
 if((buffer[0]=='W')||(buffer[0]=='w'))
 {
  int len1=getAddress(&address);
  if(len1<0)
  {
   Serial.println("Wrong address");
   return -1;         // wrong address
  }
  len1=len1+2;
  for(i=0; i<ibuffer-len1; i++)
   buffer[i]=buffer[i+len1];
  buffer[i]=0;
  len1=ibuffer-len1;
  len1=demo_eeprom_write_block(buffer, address, len1);
  Serial.print(len1); 
  Serial.print(" bytes written."); 
 }
 //-----read eeprom?--------------------------------------------
 if((buffer[0]=='R')||(buffer[0]=='r'))
 {
  int len1=getAddress(&address);
  if(len1<0)
  {
   Serial.println("Wrong address");
   return -1;         // wrong address
  }
  len1=len1+2;
  len1=getReadLen(len1);
  len1=demo_eeprom_read_block(buffer, address, len1);
  //-----show buffer--------------------------------------------
  Serial.print  ("Text   : ");
  if(len1>0)
  {
   for(int i=0; i<len1; i++) Serial.print((char)buffer[i]);
   Serial.println();
  }
  else
   Serial.println("No bytes read!");
 }
 return len1;
}

//_____analyse serial input_____________________________________
// read serial input and put it to buffer, if it is a command
// call doCommand(), if a full command is received 
// uses: Serial, buffer, BUFFER_SIZE, ibuffer
void getSerial(int len1)
{
 char c1;
 //-----command too long?---------------------------------------
 if((ibuffer+len1)>=BUFFER_SIZE)
 {
  ibuffer=-1;
  Serial.flush();
  return;
 }
 //-----for all received characters-----------------------------
 for(int i=0; i<len1; i++)
 {
  c1=Serial.read();
  //-----is beginning of a command?-----------------------------
  if(c1=='{')
  {
   ibuffer=0;
   continue;
  }
  //-----not in command mode?-----------------------------------
  if(ibuffer<0)
   continue;
  //-----is it first char, and if yes is it a command?----------
  if(ibuffer==0)
  {
   c1=toupper(c1);
   if((c1!='W')&&(c1!='R'))
    ibuffer=-1;
   else
    buffer[ibuffer++]=c1;
   continue;
  }
  //-----command finished?--------------------------------------
  if(c1=='}')
  {
   doCommand();
   Serial.flush();
   ibuffer=-1;
   return;
  }
  //-----add char to command------------------------------------
  buffer[ibuffer++]=c1;
 } 
}

//=====standard functions=======================================

void setup() {
 Serial.begin(19200);
 Serial.print("\n\nWrite and read eeprom (EEPROM size ");
 Serial.print(EEPROM_SIZE);
 Serial.println(" bytes)");
 Serial.println("--------------------------------------------");
 Serial.println("{W Hallo}  write Hallo to eeprom, address 0");
 Serial.println("{W2 Hallo} write Hallo to eeprom, address 2");
 Serial.println("{R2 4}     read 4Bytes from eeprom address 2");
 EEPROM.begin(BUFFER_SIZE);
}

void loop() {
 size_t len = Serial.available();
 if(len) {
  getSerial(len);
 }
}
