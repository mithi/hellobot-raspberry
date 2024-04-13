#define set_bit(_addr, _bit)(_addr |= 1<<_bit)
#define flip_bit(_addr, _bit)(_addr ^= 1<<_bit)
#define clear_register(_addr)(_addr = 0)

#define led_ddr DDRB
#define led_port PORTB
#define led_bit 0

void configure_timer1(){
  clear_register(TCCR1A);
  clear_register(TCCR1B);

  set_bit(TCCR1B, WGM12);                     //configure timer1 for CTC mode
  set_bit(TIMSK1, OCIE1A);                    //enable timer compare interrupt

  sei();                                      //enable global interrupts
  
  OCR1A = 15624;                              //CTC compare value 
  set_bit(TCCR1B, CS12);                      // set Fcpu/256
  //TCCR1B |= ((1 << CS10) | (1 << CS11));    // Start timer at Fcpu/64  
}

ISR(TIMER1_COMPA_vect){
  flip_bit(led_port, led_bit);             //toggle led
}

void setup() {
  
  set_bit(led_ddr, led_bit);                   //set led pin as output, pin 8
  configure_timer1();
}

void loop() {}
