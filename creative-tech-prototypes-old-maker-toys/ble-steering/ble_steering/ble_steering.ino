#include "joystick.h"
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

#define _FORWARD 0 
#define _REVERSE 1
#define _NEUTRAL 2 
#define _LEFT 0
#define _RIGHT 1  
#define _NONE 2

Joystick joystick;
Adafruit_BNO055 bno = Adafruit_BNO055(55);

int val_ori;  // val_ori-60=down, val_ori-300=up
int val_vert; // val_vert-1023=down, val_vert-0=up 
int gear; // forward, reverse, neutral
int steer; // left, right, none

void setup() {
  joystick.attach(A1, A2);
  Serial.begin(115200); 
  beginBNO(); 
}

void loop() {
  new_sensor_data();
  set_gear();
  set_steer();
  send_stuff();
  delay(100);
}

void send_stuff(){
  if (gear == _FORWARD && steer == _NONE) {
    Serial.println('a');
  }
  if (gear == _FORWARD && steer == _LEFT) {
    Serial.println('b');
  }
  if (gear == _FORWARD && steer == _RIGHT) {
    Serial.println('c');
  }
  if (gear == _NEUTRAL) {
    Serial.println('d');
  }
  if (gear == _REVERSE && steer == _NONE) {
    Serial.println('e');
  }
  if (gear == _REVERSE && steer == _LEFT) {
    Serial.println('f');
  }
  if (gear == _REVERSE && steer == _RIGHT) {
    Serial.println('g');
  }
}

void new_sensor_data(){
  sensors_event_t event; 
  bno.getEvent(&event);
  val_vert = joystick.get_vertical();
  imu::Vector<3> accel = bno.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER);
  val_ori = accel.y();
 
}

void set_gear() {
  if (val_vert > 520) {
    gear = _REVERSE;
  } else if (val_vert < 500) {
    gear = _FORWARD;
  } else {
    gear = _NEUTRAL;
  }
}

void set_steer() {
  if (val_ori > 4) {
    steer = _RIGHT;
  } else if (val_ori < -4) {
    steer = _LEFT;
  } else {
    steer = _NONE;
  }
}

void beginBNO() {
  while(!bno.begin()) {
    Serial.print("BNOERROR"); 
    delay(500);
  }
  delay(1000);
  bno.setExtCrystalUse(true);
}

