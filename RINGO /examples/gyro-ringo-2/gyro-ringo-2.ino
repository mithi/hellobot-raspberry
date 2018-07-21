#include "Ringo.h"
#include "TurnSensor.h"
#include <Wire.h>
#include <L3G.h>

Motors motor;
Communication communication;
L3G gyro;
TurnSensor turnSensor(gyro);

void printCurrentAngles(){
  
  Serial.print(turnSensor.AccumulatedAngle());
  Serial.print("\t");
  Serial.print(turnSensor.Angle360());
  Serial.print("\t");
  Serial.println(turnSensor.Angle180());
}
void setup(){
  
  communication.Enable();
  turnSensor.Setup();
}


void loop(){
  
  turnSensor.Update();
  turnSensor.GetCurrentAngle();
  printCurrentAngles();
}


