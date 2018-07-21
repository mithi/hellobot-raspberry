/*******************************************************************
 * 
 * Written by Mithi Sevilla | DEC 8, 2015 | http://mithi.xyz
 * 
 *******************************************************************/

#include "Arduino.h"
#include "Adafruit_NeoPixel.h"

/********************************************
 * PINS
 ********************************************/

#define PIN_SERIAL_RECEIVE 0
#define PIN_LEFT_MOTOR_DIRECTION 0
#define PIN_RIGHT_MOTOR_DIRECTION 1

#define PIN_SOURCE_SELECT 4
#define PIN_RIGHT_MOTOR_DRIVE 5
#define PIN_LEFT_MOTOR_DRIVE 6
#define PIN_PIXELS 7
#define PIN_BUTTON 7
#define PIN_IR_LIGHTS 8
#define PIN_PIEZO 9

const byte PIN_CAPACITOR_BATTERY = A0;   // If PIN_SOURCE_SELECT = HIGH, BATTERY else MOTOR CAPACITOR
const byte RIGHT = A1;
const byte LEFT = A2;
const byte REAR = A3;

/********************************************
 * CONSTANTS FOR PIXELS
 ********************************************/

#define LEFT_EYE 5
#define RIGHT_EYE 4
#define TOP_FRONT 3
#define BOTTOM_FRONT 2
#define BOTTOM_REAR 1 
#define TOP_REAR 0

const byte RED = 0;         //200 
const byte ORANGE = 1;      //210 
const byte YELLOW = 2;      //220 
const byte GREEN = 3;       //020
const byte BLUE = 4;        //002
const byte PURPLE = 5;      //202 
const byte PINK = 6;        //201 
const byte AQUA = 7;        //021
const byte WHITE = 8;       //222 
const byte LIME = 9;        //120
const byte INDIGO = 10;     //102 
const byte TEAL = 11;       //012
const byte TURQUOISE = 12;  //022
const byte OFF_PIX = 13;    //000

const byte MAX_COLOR_NAME = 13;

/********************************************
 * CONSTANTS FOR SWEEPER
 ********************************************/

const bool BACKANDFORTH = 0;
const bool NORMAL = 1;
const bool FORWARD = 0;
const bool REVERSE = 1;

/********************************************
 * MISCELLANEOUS CONSTANTS
 ********************************************/

#define SERIAL_SPEED 57600

#define MAX_MOTOR_SPEED 255
#define MOTOR_FORWARD 1
#define MOTOR_REVERSE 0
#define CCW 0
#define CW 1

#define TOP 1
#define BOTTOM 0

#define ON 1
#define OFF 0

/********************************************
 * EXTERNAL VARIABLES
 ********************************************/

extern Adafruit_NeoPixel pixels;
extern bool motor_ready;
extern bool print_ready;
extern bool button_ready;
extern bool pixels_ready;

/********************************************
 * CLASSES
 ********************************************/

class Motors{
  public:
    void Enable();
    void Drive(int left_speed, int right_speed);
    void DriveWheel(int speed, byte direction_pin, byte drive_pin);
    void Stop();
    void Rotate(bool dir, int speed);
};

class Communication{
  public:
    void Enable();
    void Disable();
};

class LightSensors{
  public:
    void Enable();
    int Reading(bool side, byte pin);
    int FloorReading(byte pin);
    int SkyReading(byte pin);
};

class Pixels{
  public:
    void Enable();
    void Set(byte P, byte R, byte G, byte B);
    void LeftEye(byte R, byte G, byte B);
    void RightEye(byte R, byte G, byte B);
    void TopFront(byte R, byte G, byte B);
    void TopRear(byte R, byte G, byte B);
    void BottomFront(byte R, byte G, byte B);
    void BottomRear(byte R, byte G, byte B);
    void Color(byte pixel_name, byte color_name);
};

class Button{
  public:
    void Enable();
    void Disable();
    void Update();
    bool Pressed();
};

class Piezo{
  public:
    void Enable();
    void Play(unsigned int frequency);
};

class Sweeper{
  bool _dir;
  bool _type; 
  int _state;
  int _start;
  int _end;
  int _step;
  unsigned long _sweepsMade;
  
  public:
    void Enable(int s, int e, int st, byte x);
    int Next(bool itsTime);
    unsigned long SweepsMade();
    void ToggleDirection();
    void SetDirection(bool d);
  
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
    void Enable(unsigned long t);
    bool Tick();
    void SetInterval(unsigned long t);
};
