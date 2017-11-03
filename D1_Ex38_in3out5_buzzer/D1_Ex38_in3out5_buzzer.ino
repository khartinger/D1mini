//_____D1_oop01_in3out5_buzzer.ino_________________20171103_____
// Function: As long as button D3 is pressed, the buzzer sounds.
// Hardware: (1) WeMos D1 mini
//           (2) Buzzer shield (D5)
//           (3) Button shield (D3)

int pinButton=D3;                 // button (shield)
int pinBuzzer=D5;                 // buzzer (shield)
bool buzzer_active=false;         // needed to avoid restart

void setup() {
 pinMode(pinButton, INPUT);
 pinMode(pinBuzzer, OUTPUT);
}

void loop() {
 if(digitalRead(pinButton)==0)    // button pressed
 {
  if(!buzzer_active)              // if buzzer 
  {
   tone(pinBuzzer,440);           // tone 440Hz, endless
   buzzer_active=true;            // buzzer is active
  }
 }
 else
 {
  noTone(pinBuzzer);              // stop tone
  buzzer_active=false;            // buzzer not active
 }
}
