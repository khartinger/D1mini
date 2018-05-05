//_____D1_Ex43_statemachine1.ino______________180505-180505_____
// Demo state machine
// Blue Led lights 0.8s on - 0.4s off - 0.2s on - 0.6s off - ...
// State number is shown on Serial.
// Hardware: WeMos D1 mini
#define DELAY_LOOP             100     // 100ms 
#define STATE_LED_ON1            0     // 1. state: led on 
#define STATE_LED_OFF1           8     // 0.8s later: led off
#define STATE_LED_ON2           12     // 0.4s later: led on 
#define STATE_LED_OFF2          14     // 0.2s later: led off
#define STATE_MAX               20     // 0.6s later: loop end

const int pinLED=D4;                   // pin number blue LED
int statecounter=0;                    // actual state number

//_____setup____________________________________________________
void setup() {
 Serial.begin(115200); Serial.println();    // init Serial
 pinMode(pinLED, OUTPUT);                   // led = output
}

void loop() {
 if(statecounter==0) Serial.println("-----------------");
 Serial.print("State "+String(statecounter)+": ");
 //-----state---------------------------------------------------
 if(statecounter==STATE_LED_ON1 || statecounter==STATE_LED_ON2)
 {
  digitalWrite(pinLED, LOW);               // led on
  Serial.print("LED on");                  // Serial info
 }
 //-----state---------------------------------------------------
 if(statecounter==STATE_LED_OFF1 || statecounter==STATE_LED_OFF2)
 {
  digitalWrite(pinLED, HIGH);              // led off
  Serial.print("LED off");                 // Serial info
 }
 //-----prepare for next state----------------------------------
 Serial.println();                         // Serial lext line
 if((++statecounter)>=STATE_MAX) statecounter=0;
 delay(DELAY_LOOP);                        // wait
}
