#include "PROTO3.h"

Piezo piezo;

int melody[] = {  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4};
int note_durations[] = { 4, 8, 8, 4, 4, 4, 4, 4 }; // note durations: 4 = quarter note, 8 = eighth note, etc.

void setup() {
  piezo.enable();
}

void loop() {
  delay(1000);
  play_test();
}

void play_test(){
  for (int this_note = 0; this_note < 8; this_note++) {
    int duration = 500 / note_durations[this_note];  // to calculate the note duration, take one second divided by the note type. e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    piezo.play_tone(melody[this_note], duration);
    delay(duration * 1.30);
    piezo.play_tone(NO_TONE, duration);
  } 
}
