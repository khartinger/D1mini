//_____D1_Ex22_int_timer0_blink.ino________________20170120_____
// ESP8266 (low level) timer interrupt example:
//   blue LED blinks with 1 Hz 
// Hardware: D1mini
#define TIMER_TICKS (80000L*500)  // 80MHz: 80000=1ms
const int pinLED=D4;

//_____timer 0 interrupt service routine________________________
void timer0_ISR (void) {
 digitalWrite(pinLED, digitalRead(pinLED)^1);    // invert LED
 timer0_write(ESP.getCycleCount() + TIMER_TICKS);// reload timer
}

void setup() {
 pinMode(pinLED, OUTPUT);              // LED pin is output
 noInterrupts();                       // forbid interrupts
 timer0_isr_init();                    // init timer0 interrupt
 timer0_attachInterrupt(timer0_ISR);   // interrupt service rout
 timer0_write(ESP.getCycleCount() + TIMER_TICKS);// reload timer
 interrupts();                         // allow interrupts
}

void loop() {
 yield();                              // or delay(0); 
}
