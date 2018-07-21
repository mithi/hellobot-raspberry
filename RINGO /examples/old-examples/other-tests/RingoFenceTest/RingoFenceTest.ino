
#include "Ringo.h"

Motors motor;
Communication communication;
LightSensors lightsensor;
Piezo piezo;
Button button;
Pixels pixel;

const int motor_speed = 200; 

void setup() {
  initialize();
}

void loop() {
  fenceAlgo();
}

void alert(byte color1, byte color2, int freq, int del){
  
  piezo.Play(freq);
  pixel.Color(TOP_REAR, color1);
  pixel.Color(TOP_FRONT, color2);
  delay(del);
}

void animation(){

  const int del = 70; 
  const int number_of_blinks = 3;
  const int stop_delay = 20;
  const int minFreq = 500;
  const int maxFreq = 2500; 
  
  int randomColor1 = random(0, MAX_COLOR_NAME);
  int randomColor2 = random(0, MAX_COLOR_NAME);
  int randomFrequency = random(minFreq, maxFreq);
    
  for(int x = 0; x < number_of_blinks; x++){
    alert(randomColor1, randomColor2, randomFrequency, del);
    alert(OFF_PIX, OFF_PIX, 0, stop_delay);
  }
}

void randomEyes(){
  const int NUM_COLOR = MAX_COLOR_NAME - 1;
  pixel.Color(LEFT_EYE, random(0, NUM_COLOR));
  pixel.Color(RIGHT_EYE, random(0, NUM_COLOR));  
}

void backupAndRandomTurn(bool backUp){

  const int del_min1 = 300;
  const int del_max1 = 500;

  const int del_min2 = 50;
  const int del_max2 = 1000;
  
  backUp ? motor.Drive(-motor_speed, -motor_speed) : motor.Drive(motor_speed, motor_speed);    
  delay(random(del_min1, del_max1));
  
  motor.Drive(-MAX_MOTOR_SPEED, MAX_MOTOR_SPEED);
  delay(random(del_min1, del_max2));
}

void fenceAlgo(){

  const int THRESH = 200;
    
  bool frontEdge = lightsensor.Reading(BOTTOM, LEFT) < THRESH || lightsensor.Reading(BOTTOM, RIGHT) < THRESH;
  bool backEdge = lightsensor.Reading(BOTTOM, REAR) < THRESH;
  
  if (frontEdge || backEdge){    
    motor.Stop();
    animation();
    backupAndRandomTurn(frontEdge);
  }else{
    randomEyes();
    motor.Drive(motor_speed, motor_speed);
  }
}

void initialize(){
  
  motor.Enable(); //communication.Enable();
  lightsensor.Enable();
  pixel.Enable(); //button.Enable();
  piezo.Enable();
}
