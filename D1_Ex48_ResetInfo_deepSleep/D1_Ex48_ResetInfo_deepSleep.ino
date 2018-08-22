//_____D1_Ex48_ResetInfo_deepSleep.ino________180822-180822_____
// On start D1mini checks reset info and the blue led blinks
// the number of start reason.
// In case of REASON_DEFAULT_RESET=0, blue led blinks once ;)
// REASON_DEEP_SLEEP_AWAKE=5      // awake after deep sleep
// REASON_EXT_SYS_RESET=6         // Power on
// Hardware: WeMos D1 mini (CONNECT D0 with RST!!!)
#include <Arduino.h>
extern "C" {
 #include <user_interface.h>
}
#define pinLED D4

void setup() {
 rst_info *pInfo;
 int i, reason;
 pinMode(pinLED, OUTPUT);         // pin D4 is output (blue LED)
 digitalWrite(pinLED, HIGH);      // blue LED off
 pinMode(D0, WAKEUP_PULLUP);      // connect D0->RST
 pInfo = ESP.getResetInfoPtr();   // pointer to resetinfo struct
 reason=pInfo->reason;            // get reason number (uint32)
 if(reason<1) reason=1;           // change default 0 to 1
 delay(1000);                     // wait 1s
 for(i=0; i<reason; i++)
 {
 	digitalWrite(pinLED, LOW);      // blue LED on
 	delay(500);                     // wait 0,5s
 	digitalWrite(pinLED, HIGH);     // blue LED off
 	delay(500);                     // wait 0,5s
 }
 digitalWrite(pinLED, HIGH);
 ESP.deepSleep(5 * 1000000L);
 delay(200);
}

void loop() { }
