
#include "bitmacro.h"
#define d 250
// button - portd - bit0123456 arduino uno digital pin 0, 1, 2, 3, 4, 5, 6 respectively
// led - portb - bit012345 arduino uno digital pin 8, 9, 10, 11, 12, 13 respectively

void setup() {
  write_bitmask(DDRB, 0xFF);  //make all pins of port B output 
  write_bitmask(DDRD, 0);     //make all pins of port D input
  write_bitmask(PORTD, 0xFF); //enable pull up in all pins of port D

  while(1)
    write_bitmask(PORTB ,~PIND);  
}

void loop() {}
