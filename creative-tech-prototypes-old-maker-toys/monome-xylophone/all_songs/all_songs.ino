#include <Wire.h>
#include <Adafruit_PWMServoDriver.h> 

Adafruit_PWMServoDriver driver = Adafruit_PWMServoDriver();
enum note{DOL, RE, MI, FA, SOL, LA, TI, DOH, REST}; 

struct Link {
  enum note note_id; 
  int hit_val; 
  int rest_val; 
};

struct Melody{
  int tune_size;
  int wait_time; 
  enum note tune[150]; 
};
 
/**********************************************************/
/**********************************************************/
/**********************************************************/

struct Melody twinkle{
 16, 250,
 {DOL, DOL, SOL, SOL, LA, LA, SOL, REST, FA, FA, MI, MI, RE, RE, DOL, REST},
};

struct Melody birthday{
 14, 150,
 {DOL, DOL, RE, DOL, FA, MI, REST, DOL, DOL, RE, DOL, SOL, FA, REST},
};

struct Melody comic{
  15, 100,
 {DOH, REST, SOL, SOL, REST, LA, REST, SOL, REST, REST, REST, TI, REST, DOH, REST},
};

struct Melody next_episode{
  16, 200, {
    MI, REST, TI, REST, 
    TI, LA, TI, REST, 
    LA, SOL, LA, REST, 
    LA, SOL, MI, SOL }
};

struct Melody sweet_child_of_mine{
  72, 80, {
  SOL, SOL, SOL, SOL, 
  REST, REST, FA, MI, 
  FA, REST, SOL, RE, 
  REST, REST, REST, FA,
  REST, FA, REST, MI,
  FA, REST, MI, REST, 
  REST, REST, DOL, FA, 
  REST, FA, REST, FA, 
  REST, REST, REST, FA, 
  REST, REST, MI, FA, 
  REST, REST, SOL, FA, 
  REST, MI, REST, REST,
  
  SOL, REST, SOL, REST, 
  REST, REST, LA, SOL, 
  REST, REST, FA, REST, 
  FA, REST, MI, FA, 
  REST, MI, REST, REST,
  REST, REST, REST, REST }
};

struct Melody seven_nation_army{
  144, 50, {
  LA, REST, REST, REST, REST, REST, LA, REST, 
  DOH, REST, REST, LA, REST, REST, SOL, REST,
  FA, REST, REST, REST, REST, REST, REST, REST,
  MI, REST, REST, REST, REST, REST, REST, REST, 
  LA, REST, REST,REST, REST, REST, LA, REST, 
  DOH, REST, REST, LA, REST, REST, SOL, REST, 
  FA, REST, REST, SOL, REST, REST, FA, REST, 
  MI, REST, REST, REST, REST, REST, REST, REST,

  LA, REST, REST, REST, REST, REST, LA, REST, 
  DOH, REST, REST, LA, REST, REST, SOL, REST,
  FA, REST, REST, REST, REST, REST, REST, REST,
  MI, REST, REST, REST, REST, REST, REST, REST, 
  LA, REST, REST,REST, REST, REST, LA, REST, 
  DOH, REST, REST, LA, REST, REST, SOL, REST, 
  FA, REST, REST, SOL, REST, REST, FA, REST, 
  MI, REST, REST, REST, REST, REST, REST, REST,

  DOL, REST, DOL, REST, DOL, REST, DOL, REST,
  RE, REST, RE, REST, RE, REST, RE, REST }
};

/**********************************************************/
/**********************************************************/
/**********************************************************/

struct Link link[8];
int mode = 0; // mode = 0 is controlled by computer input, mode = 1 just plays the available songs in a loop

void setup() {
  
  Serial.begin(115200); 
  driver.begin();
  driver.setPWMFreq(60);
  initialize_links();  
  calibrate_links();

  mode = floor(random(0, 2));
}

void loop() {

  mode == 1 ? looping_loop() : controllable_loop();
}

void up_all(){
  for(int x = 0; x < 8; x++)
    driver.setPWM(link[x].note_id, 0, link[x].rest_val);
}
void smash(struct Link &this_link){
  driver.setPWM(this_link.note_id, 0, this_link.hit_val);
}

void controllable_loop(){

  calibrate_links();
  calibrate_links();
  calibrate_links();

  while(1){
    
    if (Serial.available()){
      
      int val = Serial.read();
      
      for(int x = 0; x < 8; x++){
        boolean must_hit = (val & 1 << x) >> x;
        if(must_hit) smash(link[x]);
      }
      
      delay(60);
    }
    up_all();
  }
}

void looping_loop(){
  
  int wait = 2000;
  
  play_melody(twinkle);
  play_melody(twinkle);
  delay(wait);
  
  play_melody(birthday);
  play_melody(birthday);
  delay(wait);
  
  play_melody(comic);
  play_melody(comic);
  delay(wait);
  
  play_melody(seven_nation_army);
  play_melody(seven_nation_army);
  play_melody(seven_nation_army);
  delay(wait);
  
  play_melody(sweet_child_of_mine);
  play_melody(sweet_child_of_mine);
  delay(wait);
  
  play_melody(next_episode);
  play_melody(next_episode);
  play_melody(next_episode);
  play_melody(next_episode);
  delay(wait);
}

void play_melody(struct Melody this_melody){
  for(int x = 0; x < this_melody.tune_size; x++)
    this_melody.tune[x] == REST ? delay(2*this_melody.wait_time) : hit(link[this_melody.tune[x]], this_melody.wait_time);
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

  for(int x = 0; x < 8; x++)
    hit(link[x], msec);
    
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
