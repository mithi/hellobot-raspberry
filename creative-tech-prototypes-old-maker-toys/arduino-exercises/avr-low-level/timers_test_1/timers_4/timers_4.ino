//CAUTION DOES NOT WORK FOR NOW

#define set_bit(_addr, _bit)(_addr |= 1<<_bit)
#define check_bit(_addr, _bit)( _addr & 1<<_bit)
#define clear_register(_addr)(_addr = 0)

void configure_timer1(){
  clear_register(TCCR1A);
  clear_register(TCCR1B);

  set_bit(TCCR1B, WGM12);                     //configure timer1 for CTC mode
  set_bit(TCCR1A, COM1B0);                    // enable timer 1 compare output channel A in toggle mode (pin 9 or PB1 where the led will be)
  
  OCR1A = 15624;                              //CTC compare value 
  set_bit(TCCR1B, CS12);                      // set Fcpu/256
  //TCCR1B |= ((1 << CS10) | (1 << CS11));    // Start timer at Fcpu/64
}

void setup() {
  
  set_bit(PORTB, 1);                   //set led pin as output, pin 9
  configure_timer1();
}

void loop() {}

