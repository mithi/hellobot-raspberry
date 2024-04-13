#include "DFRobotRomeoBLEMini.h"

DFRobotRomeoBLEMini motors;

void setup() { 
  Serial.begin(115200);
}

void loop() {
  
  char val;
  
  if (Serial.available() > 0) {
    val = Serial.read();
  }

  switch(val) {
    case 'a':
    forward();
    break;
    case 'b':
    forward_left();
    break;
    case 'c':
    forward_right();
    break;
    case 'd':
    brake();
    break;
    case 'e':
    reverse();
    break;
    case 'f':
    reverse_left();
    break;
    case 'g':
    reverse_right();
    break;
    default: break;
  }
}

void forward(){
  motors.speed(255, 255);
}

void forward_left(){
  motors.speed(50, 250);
}

void forward_right(){
  motors.speed(250, 100);
}

void reverse(){ 
  motors.speed(-255, -255);
}

void reverse_left(){
  motors.speed(-150, -200);
}

void reverse_right(){
  motors.speed(-250, -150);
}

void brake(){
  motors.speed(0, 0);
}
