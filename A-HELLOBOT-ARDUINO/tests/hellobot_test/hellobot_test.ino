#include "robot.h"
#include <Servo.h>
#include <Adafruit_NeoPixel.h>

#define BRIGHTNESS 50
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMBER_OF_PIXELS, PIN_PIXEL, NEO_GRBW + NEO_KHZ800);

Motors motors;
Servo left_arm, right_arm;
DistanceSensor left_distance, center_distance, right_distance;

const char NO_COMMAND = 'N';
const char MOVE_ARMS = 'A';
const char TURN_LEFT = 'L';
const char TURN_RIGHT = 'R';
const char MOVE_FORWARD = 'F';
const char MOVE_BACKWARD = 'B';
const char LISTENING = 'H';
const char MESSAGE_DECODED = 'D';
const char SMART_FORWARD = 'S';
const int  MAX_COUNT = 100;

int WAIT = 1500;
int count = 0;
char current_command = NO_COMMAND;

void setup() {
  
  Serial.begin(9600);
  motors.begin();
  
  //left_arm.attach(PIN_SERVO_LEFT);
  //right_arm.attach(PIN_SERVO_RIGHT);
  
  left_distance.attach(PIN_DISTANCE_SENSOR_LEFT);
  center_distance.attach(PIN_DISTANCE_SENSOR_CENTER);
  right_distance.attach(PIN_DISTANCE_SENSOR_RIGHT); 

  strip.setBrightness(BRIGHTNESS);
  strip.begin();
  strip.show(); 

  //neopixel_test();
  
  enable_distance_detection();
  disable_distance_detection(); 
}

void loop() {
  
  if(Serial.available()) {
    
    char new_byte = char(Serial.read());
    
    if (new_byte != '\n'){
      count = 0;
      current_command = char(new_byte);
    }
    
    if (current_command == SMART_FORWARD){
      enable_distance_detection();
    }
  }
  
  if (current_command == LISTENING){
    listening();  
  } else if (current_command == MESSAGE_DECODED){
    message_decoded();    
  } else if (current_command == MOVE_ARMS){
    move_arms();    
  } else if (current_command == MOVE_FORWARD){
    forward();          
  } else if (current_command == MOVE_BACKWARD){
    backward();
  } else if (current_command == TURN_LEFT){
    left();    
  } else if (current_command == TURN_RIGHT){
    right();    
  } else if (current_command == SMART_FORWARD){
    smart_forward();
  }
}

void right(){
  motors.turn_right();
  delay(WAIT);
  motors.stop();
  current_command = NO_COMMAND;
}

void left(){
  motors.turn_left();
  delay(WAIT);
  motors.stop();
  current_command = NO_COMMAND;
}

void backward(){
  motors.move_backward();
  delay(WAIT);
  motors.stop();
  current_command = NO_COMMAND;
}

void forward(){
  motors.move_forward();
  delay(WAIT);
  motors.stop();
  current_command = NO_COMMAND;
}

void listening(){
  //rainbowFade2White(3,3,1);
  //colorWipe(strip.Color(255, 0, 255), 15);
  colorWipe(strip.Color(255, 255, 0), 15); 
  colorWipe(strip.Color(0, 255, 255), 15); 
  current_command = NO_COMMAND;
}

void message_decoded(){
  colorWipe(strip.Color(255, 0, 255), 15);
  colorWipe(strip.Color(0, 0, 0), 15);
  current_command = NO_COMMAND;
}

void move_arms(){

  int WAIT_TIME = 1500;
  int MAX = 180;
  int MIN = 0;
  
  left_arm.attach(PIN_SERVO_LEFT);
  right_arm.attach(PIN_SERVO_RIGHT);
   
  left_arm.write(MAX);
  right_arm.write(MIN);
  delay(WAIT_TIME);

  left_arm.write(MIN);
  right_arm.write(MAX);
  delay(WAIT_TIME);
 
  left_arm.detach();
  right_arm.detach();
  current_command = NO_COMMAND;
}

void smart_forward(){
  count++;        
  motors.move_forward();
  delay(100);

  if(obstacles_detected())
    stop_routine();
      
  if (count >= MAX_COUNT)
    stop_routine(); 
}

void stop_routine(){
  motors.stop();
  delay(100);
  whiteOverRainbow(20,75,5);
  disable_distance_detection();
  current_command = NO_COMMAND;
  count = 0;
}

boolean obstacles_detected(){
  boolean l = left_distance.obstacle_detected();
  boolean c = center_distance.obstacle_detected();
  boolean r = right_distance.obstacle_detected();
  boolean v = l || c || r;
  
  //Serial.print("count:");
  //Serial.println(count);
  //Serial.print(l);
  //Serial.print(c);
  //Serial.print(r);
  //Serial.println(v);
  return v;
}

void neopixel_test(){
  //Some example procedures showing how to display to the pixels:
  colorWipe(strip.Color(255, 0, 0), 50); // Red
  colorWipe(strip.Color(0, 255, 0), 50); // Green
  colorWipe(strip.Color(0, 0, 255), 50); // Blue
  colorWipe(strip.Color(0, 0, 0, 255), 50); // White
  whiteOverRainbow(20,75,5);  
  pulseWhite(5); 
  rainbowFade2White(3,3,1);
}
