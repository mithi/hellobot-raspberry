#include "Ringo.h"
#include <Wire.h>
#include <L3G.h>

Motors motor;
Communication communication;
LightSensors lightsensor;
Piezo piezo;
Button button;
Pixels pixel;

L3G gyro;

const int32_t turnAngle45 = 0x20000000;
const int32_t turnAngle90 = turnAngle45 * 2;
const int32_t turnAngle1 = (turnAngle45 + 22) / 45;

uint32_t turnAngle = 0;
int16_t turnRate;
int16_t gyroOffset;
uint16_t gyroLastUpdate = 0;

void turnSensorSetup(){
  Wire.begin();
  gyro.init();

  gyro.writeReg(L3G::CTRL1, 0b11111111);
  gyro.writeReg(L3G::CTRL4, 0b00100000);
  gyro.writeReg(L3G::CTRL5, 0b00000000);

  delay(500);


  int32_t total = 0;
  for (uint16_t i = 0; i < 1024; i++){
    while(!gyro.readReg(L3G::STATUS_REG) & 0x08);
    gyro.read();
    total += gyro.g.z;
  }
  
  gyroOffset = total / 1024;

  turnSensorReset();
  
  //while (1){
  //  turnSensorUpdate();   
  //  Serial.println((((int32_t)turnAngle >> 16) * 360) >> 16);
  //}
}

void turnSensorReset(){
  gyroLastUpdate = micros();
  turnAngle = 0;
}

void turnSensorUpdate(){
  gyro.read();
  turnRate = gyro.g.z - gyroOffset;

  uint16_t m = micros();
  uint16_t dt = m - gyroLastUpdate;
  gyroLastUpdate = m;

  int32_t d = (int32_t)turnRate * dt;
  turnAngle += (int64_t)d * 14680064 / 17578125;
}

void initialize(){
  
  motor.Enable(); //communication.Enable();
  lightsensor.Enable();
  pixel.Enable(); //button.Enable();
  piezo.Enable();
}

void setup(){
  
  initialize();
  turnSensorSetup();
  delay(500);
}

void loop(){ 
  
  turnSensorUpdate();
  int32_t pos = (((int32_t)turnAngle >> 16) * 360) >> 16;
  int32_t target = -90;
  int32_t error = target - pos;
  int32_t turnSpeed = 10*error - turnRate / 20;
  turnSpeed = constrain(turnSpeed, -255, 255);
  motor.Drive(-turnSpeed, turnSpeed); 
}


