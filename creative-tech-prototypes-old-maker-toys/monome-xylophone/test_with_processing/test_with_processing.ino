#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver driver = Adafruit_PWMServoDriver();

enum note{DOL, RE, MI, FA, SOL, LA, TI, DOH, REST}; 

char val;

struct Link {
  enum note note_id; 
  int hit_val; 
  int rest_val; 
};

struct Link link[8];

void setup() {
  
  Serial.begin(115200);
  driver.begin();
  driver.setPWMFreq(60);
  initialize_links();  
  up_all();
}

void loop() {
  if (Serial.available()){
    val = Serial.read();
    for(int x = 0; x < 8; x++){
      boolean must_hit = (val & 1 << x) >> x;
      if(must_hit)
        hit(link[x]);
    }
    delay(60);
  }
  up_all();
}

void up_all(){
  for(int x = 0; x < 8; x++)
    driver.setPWM(link[x].note_id, 0, link[x].rest_val);
}
void hit(struct Link &this_link){
  driver.setPWM(this_link.note_id, 0, this_link.hit_val);
}

void initialize_link(struct Link &this_link, enum note this_note, int hit_val, int rest_val){
  this_link.note_id = this_note;
  this_link.hit_val = hit_val;
  this_link.rest_val = rest_val; 
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
