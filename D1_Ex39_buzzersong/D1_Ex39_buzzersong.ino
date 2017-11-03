//_____D1_oop01_in3out5_buzzer.ino_________________20171103_____
// Play a little song on buzzer (just one time)
// Hardware: (1) WeMos D1 mini
//           (2) Buzzer shield
int pinBuzzer=D5;                 // Buzzer control port (D5)
const int songLength = 24;        // number of notes
char notes[]="cdefggaaaag ffffeeddddc ";
int  beats[]={1,1,1,1,2,2,1,1,1,1,2,1,1,1,1,1,2,2,1,1,1,1,3,1};
int  tempo=160;
 
void setup() 
{
 pinMode(pinBuzzer, OUTPUT);
}

void loop() 
{
 int i, duration;
 for (i=0; i<songLength; i++)     // step through the song array
 {
  duration=beats[i]*tempo;        // length of note/rest in ms
  //-----output rest or tone-------------------------------------
  if (notes[i] == ' ') noTone(pinBuzzer);
  else tone(pinBuzzer, frequency(notes[i]), duration);
  delay(duration);                // wait for tone to finish
  delay(tempo/10);                // brief pause between notes
 }
 //-----wait for D1 mini reset button (or restart)--------------
 while(true) { delay(1); }        // endless loop
 //delay(3000);                   // or wait 3sec to restart
}

//_____get frequency to specified note__________________________
int frequency(char note) 
{
 int i;
 const int numNotes = 8;          // number of stored notes
 //-----stored note names and frequencies-----------------------
 char name_[] = {'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C'};
 int  freq_[] = {262, 294, 330, 349, 392, 440, 494, 523};
 //-----search for note name in array name_---------------------
 for(i=0; i<numNotes; i++)        // Step through the notes
 {
  if(name_[i]==note) return(freq_[i]); //found->return freqency
 }
 return(0);                       // note not found
}
