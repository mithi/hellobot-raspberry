//Adafruit Metro Mini - Arduino Uno - Atmel328p 

#include "bitmacro.h"
#define bin(x)(Serial.println(x, BIN))
#define hex(x)(Serial.println(x, HEX))

void setup() {
  
  Serial.begin(115200);
  
  unsigned char x = 0;
  
  set_bit(x, 2);   bin(x); // 100
  clear_bit(x, 2); bin(x); // 0
  flip_bit(x, 3);  bin(x); // 1000
  flip_bit(x, 3);  bin(x); // 0

  write_bit(x, 0, 1); bin(x);  //1 
  
  if(has_bit_set(x, 0))
    Serial.println("True"); //should display 

  write_bit(x, 1, 1);  hex(x); //3
  write_bit(x, 1, 0);  hex(x); //1

  set_bitmask(x, 0xFE);   hex(x); //FF
  clear_bitmask(x, 0xFE); hex(x); //1
  flip_bitmask(x, 0xFE);  hex(x); //FF
  flip_bitmask(x, 0x0F);  hex(x); //F0
  write_bitmask(x, 0x08); hex(x); //8

  if(same_bitmask(x, 0x08))
    Serial.println("True"); //should display     
}

void loop() {}
