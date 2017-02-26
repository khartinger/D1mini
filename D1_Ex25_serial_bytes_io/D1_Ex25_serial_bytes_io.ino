//_____D1_Ex25_serial_bytes_io.ino_________________20170123_____
// Read byte(s) from Serial (19200 Bd), convert it to upper and
// send it back (echo).
// Blue LED blinks with 5Hz to demonstrate main loop is done.
// Hardware: WeMos D1 mini

#define BUFFER_SIZE 80
uint8_t buffer[BUFFER_SIZE];
const int pinLED=D4;

void setup() {
 pinMode(pinLED, OUTPUT);
 Serial.begin(19200);
 Serial.println("\n\nWaiting for serial input...");
}

void loop() {
 size_t len = Serial.available();
 if(len)
 {
  //-----read available bytes-----------------------------------
  if(len>BUFFER_SIZE) len=BUFFER_SIZE;
  Serial.readBytes(buffer, len);
  //-----convert to upper---------------------------------------
  for(int i=0; i<len; i++) 
   buffer[i]=toupper(buffer[i]);
  //-----write bytes back---------------------------------------
  for(int i=0; i<len; i++) 
   Serial.write(buffer[i]);
 }
 //-----blink---------------------------------------------------
 digitalWrite(pinLED, digitalRead(pinLED)^1);    // invert LED
 delay(100);
}
