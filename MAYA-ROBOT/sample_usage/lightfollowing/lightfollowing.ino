#include "PROTO3.h"

AnalogReadings light_sensor; 
Motors motors;
Pixels pixels; 

void setup() {
  light_sensor.enable(PIN_LIGHT_LEFT, PIN_LIGHT_RIGHT);
  motors.enable();
}

void loop() {
  
  int left_val = light_sensor.left();
  int right_val = light_sensor.right();
  int thresh = 200;
  int dark_thresh = 500;
  bool left_is_lighter = left_val - right_val > thresh;
  bool right_is_lighter = right_val - left_val > thresh;  
  bool its_bright = left_val > dark_thresh && right_val > dark_thresh;
  
  if (left_is_lighter){
    motors.turn_left();
  }else if (right_is_lighter){
    motors.turn_right();
  } else if (its_bright){
    motors.forward();
  } else {
    motors.stop();
  }
}


