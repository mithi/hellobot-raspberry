#include "robot.h"
#include <Adafruit_NeoPixel.h>

Motors motors;
Servo left_arm, right_arm;
DistanceSensor left_distance, center_distance, right_distance;
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMBER_OF_PIXELS, PIN_PIXEL, NEO_GRBW + NEO_KHZ800);
int incoming_byte = 0;

void setup() {
  Serial.begin(9600);
  motors.begin();
  pixels.begin();
  
  //left_arm.attach(PIN_SERVO_LEFT);
  //right_arm.attach(PIN_SERVO_RIGHT);
  left_distance.attach(PIN_DISTANCE_SENSOR_LEFT);
  center_distance.attach(PIN_DISTANCE_SENSOR_CENTER);
  right_distance.attach(PIN_DISTANCE_SENSOR_RIGHT);
  
  //individual_motor_test();
  movement_test();
  pixel_test();
  pixel_animation_test();

  //arms_test();

  //left_arm.detach();
  //right_arm.detach();

  delay(WAIT_TIME);
}

void loop(){

  
  if(Serial.available()){

    incoming_byte = Serial.read();
    
    Serial.print("I received: ");
    Serial.println(incoming_byte);
    
    distance_sensor_test();
    
    //raspberry pi sends:
    //f - forward
    //l - left
    //r - right
    //s - stop
    //a - arms
    
    //arduino sends:
    //k - successful execution of command
    //o - obstacle blockage
  }
}

void distance_sensor_test(){
  
    if(left_distance.obstacle_detected())
      Serial.println("obstacle detected at left sensor");

    Serial.print("left sensor value:");
    Serial.println(left_distance.value());

    if(center_distance.obstacle_detected())
      Serial.println("obstacle detected at center sensor");

    Serial.print("center sensor value:");
    Serial.println(center_distance.value());

    if(right_distance.obstacle_detected())
      Serial.println("obstacle detected at right sensor");
    
    Serial.print("right sensor value:");
    Serial.println(right_distance.value());
}
