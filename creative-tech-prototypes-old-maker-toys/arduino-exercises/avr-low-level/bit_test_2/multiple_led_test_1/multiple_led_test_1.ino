
#include "bitmacro.h"
#define d 250
// led - portd - bit012345 arduino uno digital pin 0, 1, 2, 3, 4, 5 respectively

void setup() {
  write_bitmask(DDRD, 0xFF); //make all pins of port b output 
}


void walker(){
  for(int x = 0; x < 6; x++){
    write_bitmask( PORTD , 1 << x);
    delay(250);
  }
}

void stairs(){
  for(int x = 0; x < 6; x++){
    set_bitmask( PORTD , 1 << x);
    delay(d);
  }
  
  for(int x = 0; x < 6; x++){
    clear_bitmask( PORTD , 1 << x);
    delay(d);
  }
}

void flipper(){
  const unsigned char x = 0b1010101;
  write_bitmask(PORTD, x);

    while(1){
      flip_bitmask(PORTD, 0xFF); //flip all bits 
      delay(d);
    }
}
void loop() {
  //walker();
  //stairs();
  flipper();
}
