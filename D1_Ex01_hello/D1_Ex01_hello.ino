//_____D1_Ex01_hello.ino___________________________20160721_____
// Hardware: WeMos D1 mini
// See:  http://www.wemos.cc/tutorial/get_started_in_arduino.html
// Simply prints Hello World to the serial monitor every 2 seconds.

void setup() {
  // initialize serial communications at 9600 bps
  Serial.begin(9600);
}

void loop() {
  Serial.println("Hello World.");
  delay(2000);
}

