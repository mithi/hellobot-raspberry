#include "joystick.h"

void Joystick::attach(int vert, int horiz){
  VERTICAL_PIN = vert;
  HORIZONTAL_PIN = horiz;   
}

int Joystick::read_axis(int this_axis){  
  int r = analogRead(this_axis);
  return r; 
}

int Joystick::get_horizontal(){
  return read_axis(HORIZONTAL_PIN);
}

int Joystick::get_vertical(){
  return read_axis(VERTICAL_PIN);
}

void Button::attach(int p, int dd){
  _pin = p;
  _delay = dd;
  pinMode(_pin, INPUT_PULLUP);
}

void Button::changed(){
  _state = _reading;
  _has_changed = HIGH;
  _state == LOW ? _just_pressed = HIGH : _just_released = HIGH;
}

void Button::no_change(){
  _has_changed = LOW;
  _just_pressed = LOW;
  _just_released = LOW;
}

void Button::update(){
  _reading = digitalRead(_pin);

  if(_reading != _last_state)
    _last_time = millis();

  if(millis() - _last_time > _delay)
    _reading != _state ? changed() : no_change();

  _last_state = _reading;
}

bool Button::has_changed(){
  update();
  return _has_changed;
}

bool Button::just_released(){
  update();
  return _just_released;
}

bool Button::just_pressed(){
  update();
  return _just_pressed;
}

bool Button::pressed(){
  update();
  return _state? LOW : HIGH;  
}