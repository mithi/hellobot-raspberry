#include "PROTO3.h"

Motors motors;

void setup() {
  motors.enable();
}


void loop() {
  //individual_motor_test();
  drive_test();
}


void individual_motor_test(){
  motors.move(LEFT_MAX_FORWARD_SPEED, STOP_MODE);
  delay(3000);
  motors.stop();
  delay(3000);

  motors.move(LEFT_MAX_REVERSE_SPEED, STOP_MODE);
  delay(3000);
  motors.stop();
  delay(3000);

  motors.move(STOP_MODE, RIGHT_MAX_FORWARD_SPEED);
  delay(3000);
  motors.stop();
  delay(3000);
  
  motors.move(STOP_MODE, RIGHT_MAX_REVERSE_SPEED);
  delay(3000);
  motors.stop();
  delay(3000);
}

void drive_test(){
  motors.forward();
  delay(3000);
  motors.stop();
  delay(3000);
  motors.reverse();
  delay(3000);
  motors.stop();
  delay(3000);
  motors.turn_left();
  delay(3000);
  motors.stop();
  delay(3000);
  motors.turn_right();
  delay(3000);
  motors.stop();
  delay(3000);
}
