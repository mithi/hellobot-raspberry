#include "bitmacro.h"

#define d 250

//blinker 1 - pin  8 - port b : bit zero 
//blinker 2 - pin  5 - port d : bit five
//blinker 3 - pin A4 - port c : bit four 

void blinker1(){
  set_bit(PORTB, 0);
  delay(d);
  clear_bit(PORTB, 0);
  delay(d);
}

void blinker2(){
  write_bit(PORTD, 5, 1);
  delay(d);
  write_bit(PORTD, 5, 0);
  delay(d); 
}

void blinker3(){
  flip_bit(PORTC, 4); 
  delay(d);
}
void setup() {
  
  set_bit(DDRB, 0);   //set data direction register port B bit zero to output (pin 8)
  set_bit(DDRD, 5);   //set data direction register port D bit five to output (pin 5)
  set_bit(DDRC, 4);   //set data direction register port C bit four to output (pin A4)
}

void loop() {
  blinker1();
  blinker2();
  blinker3();
  blinker3();
}


