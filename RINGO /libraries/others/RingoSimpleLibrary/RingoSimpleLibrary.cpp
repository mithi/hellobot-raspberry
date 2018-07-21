/*******************************************************************
 * 
 * Written by Mithi Sevilla | DEC 8, 2015 | http://mithi.xyz
 * 
 *******************************************************************/

#include "RingoSimpleLibrary.h"

/****************************************
 * VARIABLES 
 ****************************************/

bool motor_ready = 1;
bool print_ready = 0;
bool pixels_ready = 1;
bool button_ready = 0;

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(6, PIN_PIXELS, NEO_GRB + NEO_KHZ800);

/********************************************
 * MOTORS
 ********************************************/

void Motors::Enable(){

  pinMode(PIN_RIGHT_MOTOR_DIRECTION, OUTPUT);
  pinMode(PIN_LEFT_MOTOR_DIRECTION, OUTPUT);
  
  motor_ready = 1;
  print_ready = 0;
}

void Motors::Drive(int left_speed, int right_speed){

  if(!motor_ready)
    Enable();
  
  DriveWheel(left_speed, PIN_LEFT_MOTOR_DIRECTION, PIN_LEFT_MOTOR_DRIVE);
  DriveWheel(right_speed, PIN_RIGHT_MOTOR_DIRECTION, PIN_RIGHT_MOTOR_DRIVE);
}

void Motors::DriveWheel(int speed, byte direction_pin, byte drive_pin){
  
  speed = constrain(speed, -MAX_MOTOR_SPEED, MAX_MOTOR_SPEED);
  speed < 0 ? digitalWrite(direction_pin, MOTOR_REVERSE) : digitalWrite(direction_pin, MOTOR_FORWARD);
  analogWrite(drive_pin, abs(speed));
}

void Motors::Stop(){
  Drive(0, 0);
}

void Motors::Rotate(bool dir, int speed){

  speed = abs(speed);
  dir == CW ? Drive(speed, -speed) : Drive(-speed, speed);
}

void Motors::_drive_helper(int speed, bool direction, byte period){

  direction == MOTOR_FORWARD ? Drive(speed, speed) : Drive(-speed, -speed); 
  delay(period);
}

void Motors::MinToMax(int min, int max, byte period, byte incr, bool dir){
  
  min = abs(min); max = abs(max); incr = abs(incr);  

  for (byte s = min; s < max; s += incr)
    _drive_helper(s, dir, period);    
}

void Motors::MaxToMin(int max, int min, byte period, byte decr, bool dir){

  min = abs(min); max = abs(max); decr = abs(decr);  

  for (byte s = max; s > min; s -= decr)
    _drive_helper(s, dir, period);
}

void Motors::MinToMaxRotate(int min, int max, byte period, byte incr, bool dir){
  
  min = abs(min); max = abs(max); incr = abs(incr);  

  for (byte s = min; s < max; s += incr){
    Rotate(dir, s);
    delay(period);
  }  
}

void Motors::MaxToMinRotate(int max, int min, byte period, byte decr, bool dir){

  min = abs(min); max = abs(max); decr = abs(decr);  

  for (byte s = max; s > min; s -= decr){
    Rotate(dir, s);
    delay(period);
  }  
}

/********************************************
 * COMMUNICATION 
 ********************************************/

void Communication::Enable(){

  pinMode(PIN_SERIAL_RECEIVE, INPUT); 
  Serial.begin(SERIAL_SPEED); 
  
  motor_ready = 0;
  print_ready = 1;
}

void Communication::Disable(){
  
  Serial.end();
  
  pinMode(PIN_LEFT_MOTOR_DIRECTION, OUTPUT);
  pinMode(PIN_RIGHT_MOTOR_DIRECTION, OUTPUT);
  
  motor_ready = 1;
  print_ready = 0;
}

/********************************************
 * LIGHT SENSORS 
 ********************************************/

void LightSensors::Enable(){

  pinMode(REAR, INPUT);
  pinMode(LEFT, INPUT);
  pinMode(RIGHT, INPUT);
  pinMode(PIN_IR_LIGHTS, OUTPUT);

  digitalWrite(PIN_IR_LIGHTS, LOW);
  digitalWrite(PIN_SOURCE_SELECT, LOW);
}

int LightSensors::Reading(bool side, byte pin){
  
  return side == BOTTOM ? FloorReading(pin) : SkyReading(pin);
}

int LightSensors::FloorReading(byte pin){

  digitalWrite(PIN_IR_LIGHTS, HIGH);  
  digitalWrite(PIN_SOURCE_SELECT, LOW);

  delayMicroseconds(180);
  
  int val = analogRead(pin);
  
  digitalWrite(PIN_IR_LIGHTS, LOW); 
  
  return val;
}

int LightSensors::SkyReading(byte pin){

  digitalWrite(PIN_SOURCE_SELECT, HIGH);  
  return analogRead(pin);
}



/********************************************
 * PIXELS
 ********************************************/

void Pixels::Enable(){

  pinMode(PIN_PIXELS, OUTPUT);
  digitalWrite(PIN_PIXELS, LOW);
  pixels_ready = 1;
  button_ready = 0;
};

void Pixels::Set(byte P, byte R, byte G, byte B){

  if(!pixels_ready)
    Enable();

  R = constrain(R, 0, 255);
  G = constrain(G, 0, 255);
  B = constrain(B, 0, 255);

  pixels.setPixelColor(P, pixels.Color(R , G ,B));
  pixels.show();
}

void Pixels::LeftEye(byte R, byte G, byte B){
  Set(LEFT_EYE, R, G, B);
}

void Pixels::RightEye(byte R, byte G, byte B){
  Set(RIGHT_EYE, R, G, B);
}

void Pixels::TopFront(byte R, byte G, byte B){
  Set(TOP_FRONT, R, G, B);
}

void Pixels::TopRear(byte R, byte G, byte B){
  Set(TOP_REAR, R, G, B);
}

void Pixels::BottomFront(byte R, byte G, byte B){
  Set(BOTTOM_FRONT, R, G, B);
}

void Pixels::BottomRear(byte R, byte G, byte B){
  Set(BOTTOM_REAR, R, G, B);
}

void Pixels::Color(byte p, byte c){

  c = constrain(c, 0, MAX_COLOR_NAME);

  byte h = 100;
  byte m = 150;
  byte red[] =   {m, m, m, 0, 0, m, m, 0, m, h, h, 0, 0, 0};
  byte green[] = {0, h, m, m, m, 0, 0, m, m, m, 0, h, m, 0};
  byte blue[] =  {0, 0, 0, 0, m, m, h, h, m, 0, m, m, m, 0};
  
  Set(p, red[c], green[c], blue[c]);  
}

/********************************************
 * BUTTON
 ********************************************/

void Button::Enable(){
  
  pinMode(PIN_BUTTON, INPUT_PULLUP);

  pixels_ready = 0;
  button_ready = 1;
}

void Button::Disable(){

  pinMode(PIN_PIXELS,OUTPUT);

  digitalWrite(PIN_PIXELS, LOW);
  
  pixels_ready = 1;
  button_ready = 0;
}

bool Button::Pressed(){  
  
  if(!button_ready)
    Enable();
  
 if(!digitalRead(PIN_BUTTON))
    _delay_ms(50);

 return !digitalRead(PIN_BUTTON) ? 1 : 0; 
}

/********************************************
 * PIEZO
 ********************************************/

void Piezo::Enable(){
    pinMode(PIN_PIEZO, OUTPUT);
}

void Piezo::Play(unsigned int frequency){

  //frequency is in Hz
  
  uint16_t temp;
  uint16_t period, duty_cycle;
  uint8_t prescaler_bits;
  unsigned int amplitude = 100;

  if(F_CPU / frequency / 2 >= 0x10000){

    if(F_CPU / frequency / 2 >= 0x10000 * 8){
        
        prescaler_bits = 0b011; // prescaler 64
        period = F_CPU / frequency / ( 2 * 16);
        duty_cycle=  F_CPU / 1000000 * amplitude / 2 / 64;               
    
    }else{

      prescaler_bits = 0b010; // prescaler 8
      period = F_CPU / frequency / ( 2 * 8 );
      duty_cycle= F_CPU / 1000000 * amplitude / 2 / 8;
    }
  }
  else{

    prescaler_bits = 0b001;  // on but no prescaling
    period = F_CPU / frequency / ( 2*1 );
    duty_cycle = F_CPU/ 1000000 * amplitude / 2 / 1;
  }
  
  TCCR1B &= ~0b00000111; // turn off timer
  ICR1 = period;
  OCR1A = duty_cycle;
  TCCR1A = (0b10 << 6) | 0b10; //COM1A1 COM1A0, and WGM11 WGM10
  TCCR1B = (0b10 << 3 ) | prescaler_bits; // WGM13 WGM12, and off/(on with prescaler)

  pinMode(PIN_PIEZO,OUTPUT); // make PortB pin1 an output   
}

/**********************************
 * SWEEPER
 **********************************/

void Sweeper::Enable(int s, int e, int st, byte x) {

  if (s < e) {
    _dir = FORWARD;
    _start = s;
    _end = e;
    _state = s - st;
  } else {
    _dir = REVERSE;
    _start = e;
    _end = s;
    _state = s + st;
  }

  _sweepsMade = 0;
  _step = st;
  _type = x;
}

int Sweeper::Next(bool itIsTime) {

  if (itIsTime) {

    if(_type == NORMAL) {
      _dir == FORWARD ? _forward() : _reverse(); 
    } else {
      _dir == FORWARD ? _backAndForthForward() : _backAndForthReverse();
    }
  }

  return _state;
}

unsigned long Sweeper::SweepsMade(){
  return _type == NORMAL ? _sweepsMade : _sweepsMade / 2;
}

void Sweeper::SetDirection(bool d){
  _dir = d;
}

void Sweeper::ToggleDirection(){
  _dir = !_dir;
}

void Sweeper::_forward() {
  _state += _step;
  if (_state > _end) {
    _state = _start;
    _sweepsMade++;
  }
}

void Sweeper::_reverse() {
  _state -= _step;
  if (_state < _start) {
    _state = _end;
    _sweepsMade++;
  }
}

void Sweeper::_backAndForthForward(){

  if (_state < _end) {
    _state += _step;

  } else {
    _dir = REVERSE;
    _state -= _step;
    _sweepsMade++;
  }
}

void Sweeper::_backAndForthReverse(){

  if (_state > _start) {
    _state -= _step;
  } else {
    _dir = FORWARD;
    _state += _step;
    _sweepsMade++;
  }
}


/*****************************************************
 *  METRONOME
 *****************************************************/

void Metronome::Enable(unsigned long t){
  _interval= t;
  _previousTime = millis();
  _currentTime = millis();
}

void Metronome::SetInterval(unsigned long t){
  _interval= t;
}

bool Metronome::Tick(){
  _currentTime = millis();
  bool _answer = _currentTime - _previousTime >= _interval;
  if(_answer)
    _previousTime = _currentTime;
  return _answer;
}
