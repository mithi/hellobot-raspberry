#include "robot.h"

void enable_distance_detection(){
  
  pinMode(PIN_POWER_CONTROL, OUTPUT);
  delay(200);
  digitalWrite(PIN_POWER_CONTROL, HIGH);
  delay(200);
}

void disable_distance_detection(){
  digitalWrite(PIN_POWER_CONTROL, LOW);
  delay(500);  
}

void Motors::begin(){

  pinMode(PIN_MOTOR_DIRECTION_LEFT_FRONT, OUTPUT);
  pinMode(PIN_MOTOR_DIRECTION_RIGHT_FRONT, OUTPUT);
  pinMode(PIN_MOTOR_DIRECTION_LEFT_BACK, OUTPUT);
  pinMode(PIN_MOTOR_DIRECTION_RIGHT_BACK, OUTPUT);
}

void  Motors::move(int speed, int direction){

  drive(PIN_MOTOR_DIRECTION_RIGHT_BACK, PIN_MOTOR_SPEED_RIGHT_BACK, speed, direction);
  drive(PIN_MOTOR_DIRECTION_LEFT_BACK, PIN_MOTOR_SPEED_LEFT_BACK, speed, direction);
  drive(PIN_MOTOR_DIRECTION_RIGHT_FRONT, PIN_MOTOR_SPEED_RIGHT_FRONT, speed, direction);
  drive(PIN_MOTOR_DIRECTION_LEFT_FRONT, PIN_MOTOR_SPEED_LEFT_FRONT, speed, direction);
}

void Motors::rotate(int left_speed, int right_speed, int left_direction, int right_direction){

  drive(PIN_MOTOR_DIRECTION_RIGHT_BACK, PIN_MOTOR_SPEED_RIGHT_BACK, right_speed, right_direction);
  drive(PIN_MOTOR_DIRECTION_LEFT_BACK, PIN_MOTOR_SPEED_LEFT_BACK, left_speed, left_direction);
  drive(PIN_MOTOR_DIRECTION_RIGHT_FRONT, PIN_MOTOR_SPEED_RIGHT_FRONT, right_speed, right_direction);
  drive(PIN_MOTOR_DIRECTION_LEFT_FRONT, PIN_MOTOR_SPEED_LEFT_FRONT, left_speed, left_direction);
}

void Motors::drive(int direction_pin, int speed_pin, int speed, int direction){

  digitalWrite(direction_pin, direction);
  analogWrite(speed_pin, speed);
}

void Motors::turn_right(){
  rotate(RIGTH_TURNING_SPEED, RIGHT_TURNING_SPEED, REVERSE, FORWARD);
}

void Motors::turn_left(){
  rotate(LEFT_TURNING_SPEED, LEFT_TURNING_SPEED, FORWARD, REVERSE);
}

void Motors::move_forward(){
  move(SPEED, FORWARD);
}

void Motors::move_backward(){
  move(SPEED, REVERSE);
}

void Motors::stop(){
  move(0, 0);
}

void DistanceSensor::attach(int p){
  pin = p;
  pinMode(pin, INPUT);
}

int DistanceSensor::value(){
  //http://home.roboticlab.eu/en/examples/sensor/ir_distance
  //https://www.dfrobot.com/wiki/index.php/Sharp_GP2Y0A21_Distance_Sensor_(10-80cm)_(SKU:SEN0014)
  int distance;

  int value = analogRead(pin);

  if (value < 10) value = 10;
  
  distance = ((67870.0 / (value - 3.0)) - 40.0);

  return distance; 
}

int DistanceSensor::obstacle_detected(){
  return value() < DISTANCE_THRESHOLD ? 1 : 0;
}
