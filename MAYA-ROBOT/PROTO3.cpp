/*******************************************************************
 * 
 * Written by Mithi Sevilla | MAY 12, 2016 | http://mithi.xyz
 * 
 *******************************************************************/

#include "PROTO3.h"

Adafruit_NeoPixel pix = Adafruit_NeoPixel(PIXEL_NUM, PIN_PIXELS, NEO_GRB + NEO_KHZ800);
Adafruit_TiCoServo left_motor;
Adafruit_TiCoServo right_motor;

/********************************************
 * PIXELS
 ********************************************/

void Pixels::enable(){
  pinMode(PIN_PIXELS, OUTPUT);
  digitalWrite(PIN_PIXELS, LOW);
}

void Pixels::set(byte p, byte r, byte g, byte b){

  r = constrain(r, 0, 255);
  g = constrain(g, 0, 255);
  b = constrain(b, 0, 255);

  pix.setPixelColor(p, pix.Color(r, g, b));
  pix.show();
}

void Pixels::left_most(byte r, byte g, byte b){
  set(LEFT_MOST_PIX, r, g, b);
}

void Pixels::left_center(byte r, byte g, byte b){
  set(LEFT_CENTER_PIX, r, g, b);
}

void Pixels::right_center(byte r, byte g, byte b){
  set(RIGHT_CENTER_PIX, r, g, b);
}

void Pixels::right_most(byte r, byte g, byte b){
  set(RIGHT_MOST_PIX, r, g, b);
}

void Pixels::color(byte p, byte c){

  c = constrain(c, 0, MAX_COLOR_NUM);

  byte h = 75;
  byte m = 150;
  byte red[] =   {m, m, m, 0, 0, m, m, 0, m, h, h, 0, 0, 0};
  byte green[] = {0, h, m, m, m, 0, 0, m, m, m, 0, h, m, 0};
  byte blue[] =  {0, 0, 0, 0, m, m, h, h, m, 0, m, m, m, 0};
  
  set(p, red[c], green[c], blue[c]);  
}

/********************************************
 * PIEZO
 ********************************************/

void Piezo::enable(){
  pinMode(PIN_PIEZO, OUTPUT);
}

void Piezo::play_tone(unsigned int frequency, unsigned int duration){
  unsigned int period = 1000000 / frequency;
  unsigned int time_high = period / 2;

  for (long i = 0; i < duration * 1000L; i += period) {
    digitalWrite(PIN_PIEZO, HIGH);
    delayMicroseconds(time_high);
    digitalWrite(PIN_PIEZO, LOW);
    delayMicroseconds(time_high);
  }  
}

/********************************************
 * ANALOG READINGS
 ********************************************/

void AnalogReadings::enable(int l, int r){
  left_pin = l; 
  right_pin = r;
  pinMode(left_pin, INPUT);
  pinMode(right_pin, INPUT);
}

int AnalogReadings::value(int p){
  return analogRead(p);
}

int AnalogReadings::left(){
  return value(left_pin);
}

int AnalogReadings::right(){
  return value(right_pin);
}

/********************************************
 * PING (distance)
 ********************************************/

void Ping::enable(){
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
}

long Ping::duration(){

  long microseconds;

  digitalWrite(PIN_TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(PIN_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);

  pinMode(PIN_ECHO, INPUT);
  microseconds = pulseIn(PIN_ECHO, HIGH);

  return microseconds;
}

long Ping::inches(){

  long microseconds = duration();
  return microseconds / 74 / 2;
}

long Ping::centimeters(){
  
  long microseconds = duration();
  return microseconds / 29 / 2;
}

/********************************************
 * MOTORS
 ********************************************/

void Motors::enable(){
  left_motor.attach(PIN_LEFT_MOTOR);
  right_motor.attach(PIN_RIGHT_MOTOR);
}

void Motors::move(unsigned int left_speed, unsigned int right_speed){
  
  left_speed = constrain(left_speed, 0, 181);
  right_speed = constrain(right_speed, 0, 181);
  
  left_motor.write(left_speed);
  right_motor.write(right_speed);
}

void Motors::stop(){
  move(STOP_MODE, STOP_MODE);
}

void Motors::forward(){
  move(LEFT_MAX_FORWARD_SPEED, RIGHT_MAX_FORWARD_SPEED);
}

void Motors::reverse(){
  move(LEFT_MAX_REVERSE_SPEED, RIGHT_MAX_REVERSE_SPEED);
}

void Motors::turn_left(){
  move(LEFT_MAX_REVERSE_SPEED, RIGHT_MAX_FORWARD_SPEED);
}

void Motors::turn_right(){
  move(LEFT_MAX_FORWARD_SPEED, RIGHT_MAX_REVERSE_SPEED);
}
