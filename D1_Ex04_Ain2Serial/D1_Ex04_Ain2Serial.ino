//_____D1_Ex04_Ain2Serial.ino______________________20160726_____
// Analog in value sent to serial port every second
// Hardware: WeMos D1 mini
//           trimmer (poti) at pins GND-A0-3V3
const int pinAin=A0;

void setup() {
 Serial.begin(9600);              // init serial comm 9600 bps
 pinMode(pinAin, OUTPUT);
}

void loop() {
 int sensorValue = analogRead(pinAin);
 //-----Convert Ain (0...1023) to a voltage (0...3.2V):---------
 float voltage = sensorValue * (3.2 / 1023.0);
 //-----print out the value to serial---------------------------
 Serial.print(sensorValue);
 Serial.print(" = ");
 Serial.print(voltage);
 Serial.println(" V");
 delay(1000);                     // wait 1 sec
}
