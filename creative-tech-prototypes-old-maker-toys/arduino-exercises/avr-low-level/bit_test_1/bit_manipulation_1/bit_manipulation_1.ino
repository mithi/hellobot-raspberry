#define set_bit(_addr, _bit)(_addr |= 1<<_bit)
#define clear_bit(_addr, _bit)(_addr &= ~(1<<_bit))
#define flip_bit(_addr, _bit)(_addr ^= 1<<_bit)
#define check_bit(_addr, _bit)( _addr & 1<<_bit)
#define write_bit(_addr, _bit, _basis)(_basis? set_bit(_addr, _bit) : clear_bit(_addr, _bit))

void setup() {
  Serial.begin(115200);
  
  unsigned char x = 0;
  
  set_bit(x, 2);
  Serial.println(x, BIN); // 100

  clear_bit(x, 2);
  Serial.println(x, BIN); // 0

  flip_bit(x, 3);
  Serial.println(x, BIN); // 1000

  flip_bit(x, 3);
  Serial.println(x, BIN); // 0

  x = 0x01; 
  
  if(check_bit(x, 0))
    Serial.println("True"); //should display 

  write_bit(x, 1, 1);
  Serial.println(x, HEX); //3

  write_bit(x, 1, 0);
  Serial.println(x, HEX); //1
}

void loop() {
  
}
