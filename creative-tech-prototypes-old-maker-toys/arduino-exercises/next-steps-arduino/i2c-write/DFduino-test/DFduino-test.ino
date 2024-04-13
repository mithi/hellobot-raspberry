#include <Wire.h>
#include "SimpleLibrary.h"

#define METRO_MINI_ADDR 4
#define MICRO_ADDR 5

Button button1, button2, button3;

void setup() {
  
  button1.Format(0, 50);
  button2.Format(1, 50);
  button3.Format(2, 50);
  
  Wire.begin(); //join i2c bus (address optional for master)
}

void loop() {

  if(button1.JustReleased())
    wireSend(METRO_MINI_ADDR, 0);

  if(button2.JustReleased())
    wireSend(METRO_MINI_ADDR, 1);

  if(button3.JustReleased())
    wireSend(MICRO_ADDR, 2);
}

void wireSend(byte addr, byte byte_to_send){
    Wire.beginTransmission(addr);
    Wire.write(byte_to_send);
    Wire.endTransmission();
}


