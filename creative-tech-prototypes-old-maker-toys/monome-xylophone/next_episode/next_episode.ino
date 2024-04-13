#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver driver = Adafruit_PWMServoDriver();

enum note{DOL, RE, MI, FA, SOL, LA, TI, DOH, REST}; 

struct Link {
  enum note note_id; 
  int hit_val; 
  int rest_val; 
};

struct Link link[8];

enum note tune[] = {
  MI, REST, TI, REST, 
  TI, LA, TI, REST, 
  LA, SOL, LA, REST, 
  LA, SOL, MI, SOL 
  };

int tune_size = 16;

void setup() {
  
  driver.begin();
  driver.setPWMFreq(60);
  initialize_links();  
  calibrate_links();
}

void loop() {
  
  int msec = 200; 
  
  for(int x = 0; x < tune_size; x++)
    tune[x] == REST ? delay(2*msec) : hit(link[tune[x]], msec);
}

void hit(struct Link &this_link, int del){
  driver.setPWM(this_link.note_id, 0, this_link.hit_val);
  delay(del);
  driver.setPWM(this_link.note_id, 0, this_link.rest_val);
  delay(del);  
}

void initialize_link(struct Link &this_link, enum note this_note, int hit_val, int rest_val){
  this_link.note_id = this_note;
  this_link.hit_val = hit_val;
  this_link.rest_val = rest_val; 
}

void calibrate_links(){
  int msec = 300;
  hit(link[DOL], msec);
  hit(link[RE], msec);
  hit(link[MI], msec);
  hit(link[FA], msec);
  hit(link[SOL], msec);
  hit(link[LA], msec);
  hit(link[TI], msec);
  hit(link[DOH], msec);  

  delay(3*msec);
}

void initialize_links(){
  initialize_link(link[DOL], DOL, 210, 250);
  initialize_link(link[RE], RE, 200, 170);
  initialize_link(link[MI], MI, 190, 230);
  initialize_link(link[FA], FA, 155, 130);
  initialize_link(link[SOL], SOL, 150, 180);
  initialize_link(link[LA], LA, 310, 280);
  initialize_link(link[TI], TI, 160, 200);
  initialize_link(link[DOH], DOH, 195, 170);  
}
