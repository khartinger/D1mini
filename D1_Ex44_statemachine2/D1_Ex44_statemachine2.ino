//_____D1_Ex44_statemachine2.ino______________180505-180505_____
// Demo state machine 2: Special situations
// Default behavior:
// * Blue LED shines 0.8s on - 0.4s off - 0.2s on - 0.6s off ...
//   (= a long and a short blink)
// * Measure duration of every state
// * Print state number and duration on Serial (9600Bd!)
// Special condition:
// * If the blue LED is switched on, it has to stay turned on for
//   0.6sec. (Realisation: When LED is switched on, system time
//   millis() is stored. LED may only be switched off, if
//   millis()-millisLastOn is greater or equal 600)
// Hardware: WeMos D1 mini
#define DELAY_LOOP             200     // 200ms 
#define STATE_LED_ON1            0     // 1. state: led on 
#define STATE_LED_OFF1           4     // 0.8s later: led off
#define STATE_LED_ON2            6     // 0.4s later: led on 
#define STATE_LED_OFF2           7     // 0.2s later: led off
#define STATE_MAX               10     // 0.6s later: loop end

const int pinLED=D4;                   // pin number blue LED
int statecounter=0;                    // actual state number
int state_led_off1=STATE_LED_OFF1;     // 1. state turn led off
int state_led_off2=STATE_LED_OFF2;     // 2. state turn led off
long millisLastOn=0;                   // time of last led on
long loop_delay=DELAY_LOOP;            // loop delay [ms]
long loop_millis=0;                    // loop duration [ms]

//_____setup____________________________________________________
void setup() {
 Serial.begin(9600); Serial.println();      // init Serial
 pinMode(pinLED, OUTPUT);                   // led = output
}

void loop() {
 //-----prepare Serial output for one state---------------------
 loop_millis=millis();                      // get start "time"
 if(statecounter==0) Serial.println("------------------------");
 Serial.print("State "+String(statecounter)+": ");
 //-----state with special condition----------------------------
 if(statecounter==state_led_off1)
 {
  if((millis()-millisLastOn)>=600)          // special condition
  {
   Serial.print("LED off");                 // Serial info
   state_led_off1=STATE_LED_OFF1;           // for next time
   digitalWrite(pinLED, HIGH);              // led off
  }
  else                                      // do it next state
  {
   Serial.print("***NOT*** LED off");       // Serial info
   if((++state_led_off1)>=STATE_MAX) state_led_off1=0;
  }
 }
 //-----state with special condition----------------------------
 if(statecounter==state_led_off2)
 {
  if((millis()-millisLastOn)>=600)          // special condition
  {
   Serial.print("LED off");                 // Serial info
   state_led_off2=STATE_LED_OFF2;           // for next time
   digitalWrite(pinLED, HIGH);              // led off
  }
  else                                      // do it next state
  {
   Serial.print("***NOT*** LED off");       // Serial info
   if((++state_led_off2)>=STATE_MAX) state_led_off2=0;
  }
 }
 //-----state that lasts longer---------------------------------
 if(statecounter==STATE_LED_ON1 || statecounter==STATE_LED_ON2)
 {
  Serial.print("LED on");                   // Serial info
  digitalWrite(pinLED, LOW);                // led on
  millisLastOn=millis();                    // time led on
  delay(190);                               // just for test
 }
 Serial.flush();                            // wait 4 finished
 //-----prepare for next state and wait-------------------------
 if((++statecounter)>=STATE_MAX) statecounter=0; // next state
 loop_millis=millis()-loop_millis;          // loop duration
 loop_delay=loop_delay-loop_millis;         // rest delay
 if(loop_delay<0) loop_delay=0;             // time >= 0
 String s1=" ("+String(loop_millis)+"+"+String(loop_delay)+" ms)";
 Serial.println(s1);                        // Serial info
 delay(loop_delay);                         // wait
 loop_delay=DELAY_LOOP;                     // set next delay
}
