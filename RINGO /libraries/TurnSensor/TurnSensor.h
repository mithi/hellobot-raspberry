#include <Wire.h>
#include <L3G.h>
#include <Arduino.h>

class TurnSensor{

  L3G gyro;
  int16_t gyro_offset;               // average reading obtained from the gyro's Z axis during calibration.
  uint16_t gyro_last_update = 0;     // to help track how much time has passed between readings of the gyro. 
  float delta_angle = 0;             // estimated angle turned since the last time turnSensorUpdate() was called
  float accumulated_angle = 0;
  int turn_rate;                     // current angular rate of the gyro in units of 0.07 degrees per second. (-) CW (+) CCW 
  int angle360;                      // current heading -> 0 to 360
  int angle180;                      // current heading -> -180 to 180 

  public:    
  void Init();
  void Calibrate();
  void Reset();
  void Setup();
  void Update();
  void GetCurrentAngle();
  int Angle180();
  int Angle360();
  int TurnRate();
  float AccumulatedAngle();
  TurnSensor(L3G& myGyro): gyro(myGyro){
    //nothing
  }
};