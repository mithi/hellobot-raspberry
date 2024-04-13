
#include "SimpleLibrary.h"
#include <Wire.h>

#define MICRO_ADDR 5

Sweeper toggler;
Metronome metronome;
Sequencer sequence;
LedsManager leds;

int ledPins[] = {4,5,6,7,8,9};

void setup() {
  
  toggler.Format(0, 5, 1, NORMAL);
  
  metronome.Format(100);
  leds.Format(ledPins);
  sequence.Format(&leds);
  
  sequence.Start(STAIRSUP);

  Wire.begin(MICRO_ADDR);
  Wire.onReceive(receiveEvent);
 
}

void loop() {
  sequence.Update(metronome.Tick());
}

void receiveEvent(int howMany){
  int x = Wire.read(); 
  sequence.Start(toggler.Next(1));
}

