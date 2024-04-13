#include <Wire.h>
#include "SimpleLibrary.h"

#define METRO_MINI_ADDR 4

RGB rgb[2];
Sweeper sweeper;
Metronome metronome;
const int maxCount = 12; 
byte x = 0; 

void setup() {
  rgb[0].Format(0,1,2);
  rgb[1].Format(3,4,5);
  
  sweeper.Format(0, maxCount, 1, NORMAL);
  metronome.Format(500);
  
  noColor();

  Wire.begin(METRO_MINI_ADDR);
  Wire.onReceive(receiveEvent);
}

void loop() {
  if(metronome.Tick()){
    noColor();
    rgb[x].Color(sweeper.Next(1));
  }
}

void receiveEvent(int howMany){
  x = Wire.read();
  noColor(); 
}

void noColor(){
  rgb[0].ColorRaw(0, 0, 0);
  rgb[1].ColorRaw(0, 0, 0);
}
