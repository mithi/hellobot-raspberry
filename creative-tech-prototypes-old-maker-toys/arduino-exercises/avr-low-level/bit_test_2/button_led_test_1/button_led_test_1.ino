
#include "bitmacro.h"

// button - portd - bit 2 - pind - arduino digital pin 2 
// led - pord b - bit 5 - arduino digital pin 13 

#define button_as_input()(clear_bit(DDRD, 2));
#define button_pullup()(set_bit(PORTD, 2));      
#define led_as_output()(set_bit(DDRB, 5));
#define button_pressed()(!(has_bit_set(PIND, 2)))
#define set_led(x)(write_bit(PORTB, 5, x)) 

void setup() {

  button_as_input();
  button_pullup();
  led_as_output();

  while(1)
    button_debounced_pressed() ? set_led(1) : set_led(0);
}

bool button_debounced_pressed(){
  if(button_pressed())
    _delay_ms(50);

 return button_pressed() ? 1 : 0; 
}

void loop() {}


