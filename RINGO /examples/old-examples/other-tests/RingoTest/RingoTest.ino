
#include "Ringo.h"

Motors motor;
Communication communication;
LightSensors lightsensor;
Piezo piezo;
Sweeper sweeper; 
Metronome metronome;
Button button;
Pixels pixel;

void setup() {
  initialize();
}

void loop() {

  //motorTest();
  //topLightSensorTest();
  //bottomEdgeSensorTest();
  //piezoSweepTest();
  //pixelTest();  
}

void pixelTest(){
     
  pixel.TopFront(0, 0, 100);
  pixel.TopRear(0, 0, 100);

  pixel.LeftEye(100, 0, 0);
  delay(100);
  pixel.LeftEye(0, 100, 0);
  delay(100);
  pixel.LeftEye(0, 0, 100);
  delay(100);
  
}

void piezoSweepTest(){
  piezo.Play(sweeper.Next(metronome.Tick()));  
}

void bottomEdgeSensorTest(){
  Serial.println("");
  Serial.print("\t L: ");
  Serial.print(lightsensor.Reading(BOTTOM, LEFT));
  Serial.print("\t R: ");
  Serial.print(lightsensor.Reading(BOTTOM, RIGHT));
  Serial.print("\t D: ");
  Serial.print(lightsensor.Reading(BOTTOM, REAR));
}

void topLightSensorTest(){
  Serial.println("");
  Serial.print("\t L: ");
  Serial.print(lightsensor.Reading(TOP, LEFT));
  Serial.print("\t R: ");
  Serial.print(lightsensor.Reading(TOP, RIGHT));
  Serial.print("\t D: ");
  Serial.print(lightsensor.Reading(TOP, REAR));
}

void motorTest(){
  motor.Drive(255, 255);
  delay(250);
  motor.Drive(0, 0);
  motor.Drive(-255, -255);
  delay(250);
  motor.Drive(0, 0);
}

void initialize(){
  
  //motor.Enable();
  communication.Enable();

  lightsensor.Enable();
  //pixel.Enable();
  button.Enable();
  
  piezo.Enable();
  sweeper.Enable(3500, 3000, 1, BACKANDFORTH); 
  metronome.Enable(1);
}
