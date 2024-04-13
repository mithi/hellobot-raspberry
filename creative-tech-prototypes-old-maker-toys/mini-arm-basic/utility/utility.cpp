#include "utility.h"

void Sweeper::begin(int s, int e, int st, byte x) {

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

int Sweeper::next() {

  if(_type == NORMAL) {
    _dir == FORWARD ? _forward() : _reverse(); 
  } else {
    _dir == FORWARD ? _backAndForthForward() : _backAndForthReverse();
  }

  return _state;
}

unsigned long Sweeper::sweeps_made(){
  return _type == NORMAL ? _sweepsMade : _sweepsMade / 2;
}

void Sweeper::set_direction(bool d){
  _dir = d;
}

void Sweeper::toggle_direction(){
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

void Metronome::begin(unsigned long t){
  _interval= t;
  _previousTime = millis();
  _currentTime = millis();
}

void Metronome::set_interval(unsigned long t){
  _interval= t;
}

bool Metronome::tick(){
  _currentTime = millis();
  bool _answer = _currentTime - _previousTime >= _interval;
  if(_answer)
    _previousTime = _currentTime;
  return _answer;
}
