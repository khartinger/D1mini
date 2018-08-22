//_____D1_Ex42_SRF05_pulseIn.ino______________180330-180330_____
// Measure distance with a ultrasonic sensor HY-SRF05
// every two seconds and print result to Serial. 
// Pulse width is measured using pulseIn (max. 30ms blocking)
// Hardware:
// Do not connect echo pin (5V) directly to D1 mini (3V3)!
// Use different connections depending on which pins you use of
// D1 mini (reason: D3,D4 10k Pull-up, D8 10k Pull-down)
//
// VCC------------------5V      or     VCC----------------5V
// Trig-----------------D5             Trig---------------D4
// Echo---|4k7|---*-----D6             Echo-----|6k8|-----D3
//                |
//               10k
//                |
// GND------------*-----GND            GND----------------GND
//
// Macro US2CM: convert measured PWM time [us] to distance [cm].
// Formula for approximate speed of sound in dry (0% humidity)
// air see https://en.wikipedia.org/wiki/Speed_of_sound
// 
#define US2CM(us,T)     ((331.3+0.606*T)*us/20000)
#define PIN_TRIG        D5   // or D4
#define PIN_ECHO        D6   // or D3
int T=20.0;                            // Temperature in deg C

void setup() {
 Serial.begin(115200);                 // init serial comm
 pinMode(PIN_TRIG, OUTPUT);            // 
 pinMode(PIN_ECHO, INPUT);             //
 digitalWrite(PIN_TRIG, LOW);          // prepare for plus pulse
 Serial.println("\nHY-SRF05 started"); // next line, info text
}
 
void loop()
{
 long durationUs, distanceCm;          // 
 float distanceCmf;                    //distance as float value
 //-----do measuring--------------------------------------------
 Serial.println("Start measuring..."); // info text
 digitalWrite(PIN_TRIG, HIGH);         // start pulse
 delayMicroseconds(11);                // wait 11us (min.: 10us)
 digitalWrite(PIN_TRIG, LOW);          // end of pulse
 durationUs = pulseIn(PIN_ECHO, HIGH, 30000); // measure time
 distanceCm = durationUs / 29.1 / 2 ;  // calculate distance as
 distanceCmf = US2CM(durationUs,T);    // long and float
 //-----print result--------------------------------------------
 if (distanceCm <= 0){
  Serial.println("Out of range");
 }
 else {
  Serial.print(distanceCmf,0);         // no decimal places
  Serial.print("cm (float) = ");       // print unit
  Serial.print(distanceCm);            // long value
  Serial.println("cm (long)");         // print unit
 }
 delay(2000);                          // wait 2 seconds
}
