//_____D1_Ex01_blink.ino___________________________20160721_____
// Hardware: WeMos D1 mini
// Author  : karl1@hartinger1.at
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
