#include "joystick.h"
#include <Servo.h>
#include "utility.h"
 
struct Joint{
  int pin;
  int min_val;
  int max_val;
  int current_val;
  Servo servo;
  Sweeper sweeper;
};

struct Joint claw, elbow, shoulder, base;
const int time_per_tick = 10; 

Joystick left_stick, right_stick;
Metronome metronome;

void setup() {

  metronome.begin(time_per_tick);
  right_stick.attach(A0, A1);
  left_stick.attach(A3, A4);
    
  //parameters for initialize_joint: joint, pin, min_val, max_val
  initialize_joint(&claw, 11, 0, 90);
  initialize_joint(&elbow, 9, 45, 160);
  initialize_joint(&shoulder, 10, 40, 90);
  initialize_joint(&base, 6, 0, 180);
}

void loop() {

  if(metronome.tick()){
    next_action(&base, left_stick.get_horizontal() < 400, left_stick.get_horizontal() > 600);
    next_action(&claw, right_stick.get_horizontal() < 400, right_stick.get_horizontal() > 600);
    next_action(&elbow, right_stick.get_vertical() > 600, right_stick.get_vertical() < 400);
    next_action(&shoulder, left_stick.get_vertical() > 600, left_stick.get_vertical() < 400);
  }
}

void initialize_joint(struct Joint *joint, int pin, int min_val, int max_val){

  //parameters for sweeper: start, end, step_size, normal/back and forth
  joint->sweeper.begin(min_val, max_val, 1, NORMAL);

  joint->min_val = min_val;
  joint->max_val = max_val;
  joint->pin = pin;
  joint->servo.attach(pin);
  joint->current_val = (min_val + max_val)/2;
  joint->servo.write(joint->current_val); 
}

void next_action(struct Joint *joint, bool condition1, bool condition2){

  if (condition1) {
    next_pose(joint, FORWARD); 
  } else if (condition2) {
    next_pose(joint, REVERSE);  
  }
}

void next_pose(struct Joint *joint, bool dir){
    
    joint->sweeper.set_direction(dir);

    bool limit_reached = false;

    if (dir == REVERSE) {
      limit_reached = joint->current_val <= joint->min_val;
    } else if (dir == FORWARD) {
      limit_reached = joint->current_val >= joint->max_val;
    }
    
    if (!limit_reached) {
      joint->current_val = joint->sweeper.next();
      joint->servo.write(joint->current_val);
    }
}
