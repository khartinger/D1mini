//_____myWLAN.h_______________________________170228-170304_____
#ifndef MYWLAN_H
#define MYWLAN_H
 #define ADDR_SIZE     20                    //= 4 + 4ips*4bytes
 #define MDNS_SIZE     20                    //max.len local name
 #define SSID_SIZE     20                    //max.len ssid
 #define PASS_SIZE     20                    //max.len password
 char sign_[3]="CL";                         //sign for EEPROM
 char mdns_[MDNS_SIZE+1]="D1mini1";          //local.name
 char ssid_[SSID_SIZE+1]="D1mini           ";//17 chars
 char pass_[PASS_SIZE+1]="12345678";         //min. 8 char or ""
 IPAddress ip(192,168,1,110);
 IPAddress gateway(192,168,0,1);
 IPAddress subnet(255,255,252,0);
 IPAddress host(192,168,1,111);
#endif
