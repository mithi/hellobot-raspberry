#define set_bit(_addr, _bit)(_addr |= 1<<_bit)
#define flip_bit(_addr, _bit)(_addr ^= 1<<_bit)
#define check_bit(_addr, _bit)( _addr & 1<<_bit)

#define led_ddr DDRB
#define led_port PORTB
#define led_bit 0

void setup() {
  
  set_bit(led_ddr, led_bit);                   //set led pin as output, pin 8
  
  TCCR1A = 0;
  TCCR1B = 0;

  set_bit(TCCR1B, WGM12);                     //configure timer1 for CTC mode
  OCR1A = 15624;                              //CTC compare value 
  set_bit(TCCR1B, CS12);                      // set Fcpu/256
  //TCCR1B |= ((1 << CS10) | (1 << CS11));    // Start timer at Fcpu/64
  
  while(1){
    if(check_bit(TIFR1, OCF1A)){               //if OCF1A flag on TIFR register is set because TCNT overflowed OCR1A value, timer count resets at overflow
      flip_bit(led_port, led_bit);             //toggle led
      set_bit(TIFR1, OCF1A);                   //clear OCF1A flag 
    }
  }
}

void loop() {}


