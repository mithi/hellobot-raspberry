
#include "SimpleLibrary.h"
#include <Wire.h>

#define METRO_MINI_ADDR 4
RGB rgb[2];

void setup() {

  rgb[0].Format(5,6,13);
  rgb[1].Format(9,10,11);
  
  rgb[0].ColorRaw(0, 0, 0);
  rgb[1].ColorRaw(0, 0, 0);

  Wire.begin(); 
  Serial.begin(115200);
}

void loop() {
  
  Wire.requestFrom(METRO_MINI_ADDR, 3); //request 3 bytes from metro mini 
  
  while (Wire.available()){
    int r = Wire.read();
    int g = Wire.read();
    int b = Wire.read();

    Serial.print(r);
    Serial.print(" ");
    Serial.print(g);
    Serial.print(" ");
    Serial.println(b);
    
    rgb[0].ColorRaw(r, g, b);
    rgb[1].ColorRaw(r, g, b);
  }
}


