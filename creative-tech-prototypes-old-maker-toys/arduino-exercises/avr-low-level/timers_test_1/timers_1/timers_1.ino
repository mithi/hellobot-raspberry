#define set_bit(_addr, _bit)(_addr |= 1<<_bit)
#define flip_bit(_addr, _bit)(_addr ^= 1<<_bit)

#define led_ddr DDRB
#define led_port PORTB
#define led_bit 0

void setup() {
  
  set_bit(led_ddr, led_bit); //set led pin as output, pin 8
  
  TCCR1A = 0;
  TCCR1B = 0;
  set_bit(TCCR1B, CS12); // set Fcpu/256
    
  while(1){
    if(TCNT1 >= 15624){
      flip_bit(led_port, led_bit);
      TCNT1 = 0;
    }
  }
}

void loop() {}


