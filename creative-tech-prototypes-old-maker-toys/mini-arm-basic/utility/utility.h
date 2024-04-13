#include "utility_constants.h"

class Sweeper{
  bool _dir;
  bool _type; 
  int _state;
  int _start;
  int _end;
  int _step;
  unsigned long _sweepsMade;
  public:
  void begin(int s, int e, int st, byte x);
  int next();
  unsigned long sweeps_made();
  void toggle_direction();
  void set_direction(bool d);
  private:
  void _forward();
  void _reverse();
  void _backAndForthForward();
  void _backAndForthReverse();
};

class Metronome{
  unsigned long _interval; 
  unsigned long _previousTime;
  unsigned long _currentTime;
  public:
  void begin(unsigned long t);
  bool tick();
  void set_interval(unsigned long t);
};
