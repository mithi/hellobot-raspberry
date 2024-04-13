#include <Arduino.h>

class Joystick{
  int VERTICAL_PIN;
  int HORIZONTAL_PIN; 
  int RANGE;
  int CENTER;
    
  public:
    void attach(int vert, int horiz);
    int get_horizontal();
    int get_vertical();

  private:
    int read_axis(int this_axis);
};

class Button{
  bool _last_state = HIGH;
  bool _state;             //LOW if PRESSED because INPUT_PULLUP 
  bool _has_changed = 0;
  bool _just_released = 0; 
  bool _just_pressed = 0; 
  int _delay;
  int _reading;
  int _pin;
  int _last_time = 0;
  
  public:
    void attach(int p, int dd);
    bool pressed();
    bool has_changed();
    bool just_pressed();
    bool just_released();

  private: 
    void update();
    void changed();
    void no_change();
};