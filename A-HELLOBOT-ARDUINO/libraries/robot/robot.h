#include "Arduino.h"
#include <Servo.h>

const int DISTANCE_SAMPLING_RATE = 200;
const int DISTANCE_THRESHOLD = 300; //mm

const boolean FORWARD = true;
const boolean REVERSE = false;

const int SPEED = 60;
const int LEFT_TURNING_SPEED = 180;
const int RIGHT_TURNING_SPEED = 180;
const int WAIT_TIME = 2000;

const int MAX_ANGLE = 180; 
const int MIN_ANGLE = 10;
const int DEFAULT_ANGLE = 40;

const int PIN_POWER_CONTROL = 35;

const int PIN_DISTANCE_SENSOR_LEFT = A0;
const int PIN_DISTANCE_SENSOR_CENTER = A1;
const int PIN_DISTANCE_SENSOR_RIGHT = A2;

#define PIN_PIXEL 40

#define NUMBER_OF_PIXELS 16

#define PIN_SERVO_RIGHT 39
#define PIN_SERVO_LEFT 37

#define PIN_MOTOR_SPEED_LEFT_FRONT 2
#define PIN_MOTOR_DIRECTION_LEFT_FRONT 23

#define PIN_MOTOR_SPEED_RIGHT_FRONT 5
#define PIN_MOTOR_DIRECTION_RIGHT_FRONT 29

#define PIN_MOTOR_SPEED_LEFT_BACK 3
#define PIN_MOTOR_DIRECTION_LEFT_BACK 25

#define PIN_MOTOR_SPEED_RIGHT_BACK 4
#define PIN_MOTOR_DIRECTION_RIGHT_BACK 27

class Motors{

  public: 
    void begin();
    void move(int speed, int direction);
    void rotate(int left_speed, int right_speed, int left_direction, int right_direction);
    void drive(int direction_pin, int speed_pin, int speed, int direction);
    void turn_left();
    void turn_right();
    void move_forward();
    void move_backward();
    void stop();
};

class DistanceSensor{

  int pin;
  
  public: 
    void attach(int p);
    int value();
    int obstacle_detected();
};

void enable_distance_detection();
void disable_distance_detection();