
#include "bitmacro.h"

#define d 250
#define LED1(x)(write_bit(PORTB, 0, x)) //port B bit zero to output (pin 8)
#define LED2(x)(write_bit(PORTD, 5, x)) //port D bit five to output (pin 5)
#define LED3(x)(write_bit(PORTC, 4, x)) //port C bit four to output (pin A4)
#define ON 1
#define OFF 0

void setup() {

  set_bit(DDRB, 0);   //set data direction register port B bit zero to output (pin 8)
  set_bit(DDRD, 5);   //set data direction register port D bit five to output (pin 5)
  set_bit(DDRC, 4);   //set data direction register port C bit four to output (pin A4)

  infinite();
}

void infinite(){
  while(1){
    LED1(ON);
    delay(d);
    LED1(OFF);  
    delay(d);
    LED2(ON);
    delay(d);
    LED2(OFF);  
    delay(d);
    LED3(ON);
    delay(d);
    LED3(OFF);
    delay(d);
  }
}

void loop() {}


