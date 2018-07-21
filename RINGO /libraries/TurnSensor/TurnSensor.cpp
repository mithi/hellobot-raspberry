#include "TurnSensor.h"

void TurnSensor::Init(){
  
  Wire.begin();
  gyro.init();

  gyro.writeReg(L3G::CTRL1, 0b11111111); // 800 Hz output data rate // low-pass filter cutoff 100 Hz
  gyro.writeReg(L3G::CTRL4, 0b00100000); // 2000 dps full scale
  gyro.writeReg(L3G::CTRL5, 0b00000000); // High-pass filter disabled
}

void TurnSensor::Calibrate(){

  int32_t total = 0;
  
  for (uint16_t i = 0; i < 1024; i++){
    
    while(!gyro.readReg(L3G::STATUS_REG) & 0x08);   
    gyro.read();
    total += gyro.g.z;
  }
  
  gyro_offset = total / 1024;
}

void TurnSensor::Reset(){
  
  gyro_last_update = micros();
  angle180 = 0;
  angle360 = 0;
  accumulated_angle = 0;
}

void TurnSensor::Setup(){
  
  Init();
  Calibrate();
  Reset();
}

void TurnSensor::Update(){
  
  gyro.read();
  turn_rate = gyro.g.z - gyro_offset;
  
  uint16_t time_now = micros();
  uint16_t dt = time_now - gyro_last_update;
  gyro_last_update = time_now;

  delta_angle = turn_rate * 0.07 / 1000000 * dt;
  accumulated_angle += delta_angle;
}

void TurnSensor::GetCurrentAngle(){
  
  angle360 = (int)accumulated_angle % 360; 

  if ( angle360 < 0)
    angle360 += 360;

  if (angle360 > 180 && angle360 <= 360){
    angle180 = angle360 - 360;
  } else {
    angle180 = angle360; 
  }
}

int TurnSensor::Angle360(){
  return angle360;
}

int TurnSensor::Angle180(){
  return angle180;
}

float TurnSensor::AccumulatedAngle(){
  return accumulated_angle;
}

int TurnSensor::TurnRate(){
  return turn_rate;
}