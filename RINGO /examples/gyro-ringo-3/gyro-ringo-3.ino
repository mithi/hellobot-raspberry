#include "Ringo.h"
#include "TurnSensor.h"
#include <Wire.h>
#include <L3G.h>

Motors motor;
Communication communication;
L3G gyro;
TurnSensor turnSensor(gyro);

void setup(){

  motor.Enable();
  communication.Enable();
  turnSensor.Setup();
}


void loop(){

  turn(-90);
  turnSensor.Update(); // you should call this as much as possible, so use metronome.tick() instead of delay()
  delay(500);
  turnSensor.Update();
}

void turn(int target){

  int thresh = 2; 
  
  while(1){

    turnSensor.Update();
    turnSensor.GetCurrentAngle();

    int current_position = turnSensor.Angle180();
    int current_rate = turnSensor.TurnRate();
    int error = target - current_position; 
    int turn_speed = constrain(10 * error - current_rate / 20, -MAX_MOTOR_SPEED, MAX_MOTOR_SPEED);
  
    motor.Drive(-turn_speed, turn_speed);

    if (turn_speed <= thresh)
      break;
  }

  motor.Drive(0, 0);
  
  turnSensor.Calibrate();
  turnSensor.Reset();
}


