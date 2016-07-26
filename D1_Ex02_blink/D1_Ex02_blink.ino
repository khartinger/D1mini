//_____D1_Ex02_blink.ino___________________________20160721_____
// Hardware: WeMos D1 mini
const int pinLED=2;

void setup() {
 pinMode(pinLED, OUTPUT);
}

void loop() {
 digitalWrite(pinLED, HIGH);
 delay(500);
 digitalWrite(pinLED, LOW);
 delay(500);
}
