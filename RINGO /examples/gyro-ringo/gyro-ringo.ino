#include "Ringo.h"
#include <Wire.h>
#include <L3G.h>

Motors motor;
Communication communication;
L3G gyro;

float accumulated_angle = 0;
float delta_angle = 0;             // estimated angle turned since the last time turnSensorUpdate() was called
int turn_rate;                     // current angular rate of the gyro in units of 0.07 degrees per second. (-) CW (+) CCW 
int16_t gyro_offset;               // average reading obtained from the gyro's Z axis during calibration.
uint16_t gyro_last_update = 0;     // to help track how much time has passed between readings of the gyro. 
int angle360;
int angle180; 

void turnSensorInit(){
  
  Wire.begin();
  gyro.init();

  gyro.writeReg(L3G::CTRL1, 0b11111111); // 800 Hz output data rate // low-pass filter cutoff 100 Hz
  gyro.writeReg(L3G::CTRL4, 0b00100000); // 2000 dps full scale
  gyro.writeReg(L3G::CTRL5, 0b00000000); // High-pass filter disabled
}

void turnSensorCalibrate(){

  int32_t total = 0;
  
  for (uint16_t i = 0; i < 1024; i++){
    
    while(!gyro.readReg(L3G::STATUS_REG) & 0x08);   
    gyro.read();
    total += gyro.g.z;
  }
  
  gyro_offset = total / 1024;
}

void turnSensorReset(){
  
  gyro_last_update = micros();
  angle180 = 0;
  angle360 = 0;
  accumulated_angle = 0;
}

void turnSensorSetup(){
  
  turnSensorInit();
  delay(500);              // delay to give the user time to remove their finger.
  turnSensorCalibrate();
  turnSensorReset();
}

void turnSensorUpdate(){
  
  gyro.read();
  turn_rate = gyro.g.z - gyro_offset;
  
  uint16_t time_now = micros();
  uint16_t dt = time_now - gyro_last_update;
  gyro_last_update = time_now;

  delta_angle = turn_rate * 0.07 / 1000000 * dt;
  accumulated_angle += delta_angle;
}

void turnSensorGetCurrentAngle(){
  
  angle360 = (int)accumulated_angle % 360; 

  if ( angle360 < 0)
    angle360 += 360;

  if (angle360 > 180 && angle360 <= 360){
    angle180 = angle360 - 360;
  } else {
    angle180 = angle360; 
  }
}

void printCurrentAngles(){
  
  Serial.print(accumulated_angle);
  Serial.print("\t");
  Serial.print(angle360);
  Serial.print("\t");
  Serial.println(angle180);
}
void setup(){
  
  communication.Enable();
  turnSensorSetup();
}


void loop(){
  
  turnSensorUpdate();
  turnSensorGetCurrentAngles();
  printCurrentAngles();
}


