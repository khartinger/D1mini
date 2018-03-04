//_____D1_Ex41_deepSleep.ino__________________180303-180303_____
// D1mini is 5sec awake (blue led on), then 5sec deep sleep
// (e.g. for current measuring).
// Hardware: WeMos D1 mini (D0 with RST connected!)
#define pinLED D4

void setup() {
 //-----deepSleep in microseconds, connect D0-RST !!!-----------
 pinMode(pinLED, OUTPUT);
 digitalWrite(pinLED, LOW);
 delay(5000);
 digitalWrite(pinLED, HIGH);
 ESP.deepSleep(5 * 1000000L);
 delay(200);
}

void loop() { }
