//_____D1_Ex18_file1_demo__________________________20161221_____
// Test a file on the D1 mini:
// Mount the file system, print file system info, create a file,
// write data (int, string), read from file, check data read
// and delete file.
// Requirement: file system exists on D1 mini (format done)
// For SPIFFS documentation see
// https://github.com/esp8266/Arduino/blob/master/doc/filesystem.md
#include "FS.h"

//_____example: show file system info___________________________
void showFileSystemInfo(void)
{
 FSInfo fs_info;
 bool ok=SPIFFS.info(fs_info);
 if(ok)
 {
  Serial.print("  * Total Bytes:     ");
  Serial.println(fs_info.totalBytes);
  Serial.print("  * Used Bytes:      ");
  Serial.println(fs_info.usedBytes);
  Serial.print("  * Block Size:      ");
  Serial.println(fs_info.blockSize);
  Serial.print("  * Page Size:       ");
  Serial.println(fs_info.pageSize);
  Serial.print("  * Max Open Files:  ");
  Serial.println(fs_info.maxOpenFiles);
  Serial.print("  * Max Path Length: ");
  Serial.println(fs_info.maxPathLength);
 }
}

//_____setup routine____________________________________________
void setup(void){
 File f;
 bool ok=true;
 int  iTemp=0;
 String sTemp="";
 Serial.begin(9600);
 //SPIFFS.format();  // has to be done before!!
 //-------------------------------------------------------------
 Serial.print("\nMount file system... ");
 ok = SPIFFS.begin();
 if(!ok)
  Serial.println("=> ERROR while begin()  :(");
 else
 {
  Serial.println("=> success :)");
  //------------------------------------------------------------
  showFileSystemInfo();
  //------------------------------------------------------------
  Serial.print("Create a file....... ");
  f = SPIFFS.open("/test.txt","w");
  if(!f)
   Serial.println("=> ERROR while open()  :(");
  else
  {
   f.println(123);
   f.println("ABC");
   f.close();
   Serial.println("=> file created :)");
   //-----------------------------------------------------------
   showFileSystemInfo();
   //-----------------------------------------------------------
   Serial.print("Read file........... ");
   f = SPIFFS.open("/test.txt","r");
   if(!f)
    Serial.println("=> ERROR while open()  :(");
   else
   {
    iTemp = (f.readStringUntil('\n')).toInt();
    sTemp = f.readStringUntil('\n');
    sTemp.replace("\r", "");
    if((iTemp!=123)||(sTemp!="ABC"))
    {
     Serial.print("=> ERROR: Wrong data read: i=");
     Serial.print(iTemp);
     Serial.println(", s="+sTemp);
    }
    else
     Serial.println("=> data ok :)");
    //----------------------------------------------------------
    Serial.print("Delete file......... ");
    ok = SPIFFS.remove("/test.txt");
    if(!ok)
     Serial.println("=> ERROR while remove()  :(");
    else
    Serial.println("=> file deleted  :)");
    ok = SPIFFS.remove("/test.txt");
   }
  }
 }
}

//_____main loop________________________________________________
void loop(void){
 //...nothing to do...
}
