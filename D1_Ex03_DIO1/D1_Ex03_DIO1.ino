//_____D1_Ex03_DIO1.ino____________________________20160726_____
// Status of button (D3=DGPIO0) is shown on blue LED (D4=GPIO2)
// and Serial Port
// Hardware: WeMos D1 mini
//           1-Button Shield
const int pinButton=D3;
const int pinLED=D4;

void setup() {
 Serial.begin(9600);              // init serial comm 9600 bps
 pinMode(pinLED, OUTPUT);
 pinMode(pinButton, INPUT);
}

void loop() {
 int button_;
 button_= digitalRead(pinButton);
 digitalWrite(pinLED, button_);
 if(button_==0)
  Serial.println("button pressed!");
}
