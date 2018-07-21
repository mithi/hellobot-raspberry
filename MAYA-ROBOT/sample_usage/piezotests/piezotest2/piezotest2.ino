#include "PROTO3.h"

Piezo piezo;

int length = 15; // the number of notes
char notes[] = "ccggaagffeeddc "; // a space represents a rest
int beats[] = { 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 4 };
int tempo = 300;

void setup() {
  piezo.enable();
}

void loop() {
  for (int i = 0; i < length ; i++)
    notes[i] == ' ' ? delay(beats[i]*tempo): play(notes[i], beats[i]*tempo);
}

void play(char note, int duration){
  
  char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };
  int freq[] = {261, 294, 329, 349, 392, 440, 493, 523};
  
  for( int i = 0; i < 8; i++){
    if(names[i] == note)
      piezo.play_tone(freq[i], duration);
  }  
}
