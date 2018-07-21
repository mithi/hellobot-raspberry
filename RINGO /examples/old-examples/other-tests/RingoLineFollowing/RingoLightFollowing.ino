
#include "Ringo.h"

Motors motor;
Communication communication;
LightSensors lightsensor;
Piezo piezo;
Button button;
Pixels pixel;

const int motorSpeed = 250; 

void setup() {
  initialize();
}

void loop() {
  
  const int THRESH = 400;
  
  while(lightsensor.Reading(BOTTOM, LEFT) < THRESH)
    motor.Drive(-motorSpeed, motorSpeed);

  while(lightsensor.Reading(BOTTOM, RIGHT) < THRESH)
    motor.Drive(motorSpeed, -motorSpeed);

  motor.Drive(motorSpeed, motorSpeed); 
}

void initialize(){
  
  motor.Enable(); //communication.Enable();
  lightsensor.Enable();
  pixel.Enable(); //button.Enable();
  piezo.Enable();
}
