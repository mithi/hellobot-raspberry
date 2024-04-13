
#define set_bit(_addr, _bit)(_addr |= 1<<_bit)
#define clear_bit(_addr, _bit)(_addr &= ~(1<<_bit))
#define flip_bit(_addr, _bit)(_addr ^= 1<<_bit)
#define check_bit(_addr, _bit)( _addr & 1<<_bit)
#define write_bit(_addr, _bit, _basis)(_basis? set_bit(_addr, _bit) : clear_bit(_addr, _bit))

#define button_ddr DDRD
#define button_port PORTD
#define button_bit 2 
#define button_pin PIND 

#define led_ddr DDRB
#define led_port PORTB
#define led_bit 5

void setup() {
  clear_bit(button_ddr, button_bit);   
  set_bit(button_port, button_bit);    
  set_bit(led_ddr, led_bit);

  Serial.begin(115200);
}

bool button_on(){
  if(check_bit(button_pin, button_bit) == 0)
    _delay_ms(25);

 return check_bit(button_pin, button_bit) == 0 ? 1 : 0; 
}

void loop() {
 toggle_led();
 //check_button();
}

void check_button(){
  if(button_on() == 0){
    Serial.println("OFF");
  }else{
    Serial.println("ON");
  }
}

void toggle_led(){
  if(button_on() == 1){
    flip_bit(led_port, led_bit);
  }
  _delay_ms(250);  
}
