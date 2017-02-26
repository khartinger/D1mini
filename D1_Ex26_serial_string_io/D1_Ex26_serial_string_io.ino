//_____D1_Ex26_serial_string_io.ino________________20170123_____
// Read a string from serial (19200 Bd), convert it to upper
//  and send it back.
// If a character is received, readStringUntil waits until
//  endchar (e.g. \r) is received or timeout occured (2sec).
// Blue LED blinks with 5Hz to demonstrate main loop is done.
// See also https://www.arduino.cc/en/Reference/Serial
// Hardware: WeMos D1 mini

const int pinLED=D4;
String s1;

void setup() {
 pinMode(pinLED, OUTPUT);
 Serial.begin(19200);
 Serial.setTimeout(2000);         // wait max. 2000ms
 Serial.println("\n\nWaiting for serial input...");
}

void loop() {
 size_t len = Serial.available();
 if(len)
 {
  //-----read String--------------------------------------------
  //s1=Serial.readString();
  s1=Serial.readStringUntil('\r');
  //-----convert to upper---------------------------------------
  s1.toUpperCase();
  //-----write bytes back---------------------------------------
  Serial.println(s1);
 }
 //-----blink---------------------------------------------------
 digitalWrite(pinLED, digitalRead(pinLED)^1);    // invert LED
 delay(100);
}
