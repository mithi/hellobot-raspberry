#define set_bit(_addr, _bit)(_addr |= 1<<_bit)
#define clear_bit(_addr, _bit)(_addr &= ~(1<<_bit))
#define flip_bit(_addr, _bit)(_addr ^= 1<<_bit)
#define check_bit(_addr, _bit)( _addr & 1<<_bit)
#define write_bit(_addr, _bit, _basis)(_basis? set_bit(_addr, _bit) : clear_bit(_addr, _bit))

#define d 250

void blinker1(){
  set_bit(PORTB, 0);      //set port B bit zero to high (pin 8)
  delay(d);
  clear_bit(PORTB, 0);    //set port B bit zero to low  (pin 8)
  delay(d);
}

void blinker2(){
  write_bit(PORTD, 5, 1);    //set port D bit one to high (pin 5)
  delay(d);
  write_bit(PORTD, 5, 0);    //set port D bit one to low  (pin 5)
  delay(d); 
}

void blinker3(){
  flip_bit(PORTC, 4); 
  delay(d);
}
void setup() {
  
  set_bit(DDRB, 0);   //set data direction register port B bit zero to output (pin 8)
  set_bit(DDRD, 5);   //set data direction register port D bit one to output (pin 5)
  set_bit(DDRC, 4);   //set data direction register port C bit one to output (pin A4)
}

void loop() {
  blinker1();
  blinker2();
  blinker3();
  blinker3();
}


