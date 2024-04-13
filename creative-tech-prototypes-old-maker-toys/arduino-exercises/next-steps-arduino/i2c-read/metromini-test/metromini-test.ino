#include <Wire.h>
#include "SimpleLibrary.h"
#include "Tunes.h"

#define METRO_MINI_ADDR 4

AnalogInput pot[3];
Buzzer buzzer;

void setup() {

  pot[0].Format(A0);
  pot[1].Format(A1);
  pot[2].Format(A2);

  buzzer.Format(8, 1.5, 1000);

  Wire.begin(METRO_MINI_ADDR);
  Wire.onRequest(requestEvent);
}

void requestEvent(){
  char x[3];
  x[0] = char(pot[0].MappedValue(0, 255));
  x[1] = char(pot[1].MappedValue(0, 255));
  x[2] = char(pot[2].MappedValue(0, 255));

  Wire.write(x);
}

void loop() {
  
  playImperialMarch();
  playGameOfThrones();
} 

void playMusicFloat(int tune[], float tempo[], int tuneSize){
  for(int note = 0; note < tuneSize; note++)
    buzzer.PlayNote(tune[note], tempo[note]);
}

void playMusicFade(int tune[], int period[], int tuneSize){
  for(int note = 0; note < tuneSize; note++)
    buzzer.Play(tune[note], period[note], period[note]+25);
}

void playImperialMarch(){
  
  playMusicFloat(firstTuneA, tuneTempo1, tuneSize);
  playMusicFloat(firstTuneB, tuneTempo1, tuneSize);

  playMusicFloat(secondTuneA, tuneTempo2A, tuneSize);
  playMusicFloat(secondTuneB, tuneTempo2B, tuneSize);

  playMusicFloat(variantTune1, variantTuneTempo, tuneSize);

  playMusicFloat(secondTuneA, tuneTempo2A, tuneSize);
  playMusicFloat(secondTuneB, tuneTempo2B, tuneSize);

  playMusicFloat(variantTune2, variantTuneTempo, tuneSize);
}

void GOTBackTune14x(){
  for(int x=0; x<4; x++)
    playMusicFade(backTune1, backTune1Period, backTuneSize);
}

void GOTBackTune24x(){
  for(int x=0; x<4; x++)
    playMusicFade(backTune2, backTune2Period, backTuneSize);
}
void playGameOfThrones(){
  GOTBackTune14x();
  playMusicFade(tune1, tunePeriod, GOTTuneSize);
  GOTBackTune14x();
  playMusicFade(tune2, tunePeriod, GOTTuneSize);
  GOTBackTune14x();
  playMusicFade(tune3, tunePeriod, GOTTuneSize);
  GOTBackTune14x();
  playMusicFade(tune4, tunePeriod, GOTTuneSize);
  GOTBackTune14x();
  playMusicFade(tuneX, tunePeriodX, tuneXSize);
  GOTBackTune24x();
}
