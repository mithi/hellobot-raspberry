import processing.sound.*;

int n = 8; //number of rows
int m = 16; // number of cols
int sz = 50; //size of button
int incr = 1; // increment tempo
int min_tempo = 2;   // minimum tempo
int max_tempo = 25;  // maximum tempo 

int tempo = 10;
int counter = 0; 
int prev_i; 
int prev_j; 
int current_col = 0; 
int prev_col = m - 1; 

Button[][] buttons;
SoundFile[] sounds;

void setup(){
  
  size(800, 400); // sz*m, sz*n
  background(255);
  initialize_sounds();
  initialize_buttons();
}

void draw(){
  
  hover();
  
  if(counter == tempo){
    
    counter = 0;
    next_current_col(); 
    update();
  }
  counter++;
}

void mousePressed(){
  
  int i = mouseX / sz;
  int j = mouseY / sz; 
  
  buttons[i][j].on = !buttons[i][j].on;
  buttons[i][j].update_and_display();
}

void keyPressed(){
  
  if (key == 'q' || key == 'Q' && tempo <= max_tempo){
    tempo+=incr;
    counter = 0;
    println(tempo);
  }

  if (key == 'a' || key == 'A' && tempo >= min_tempo){
    tempo-=incr;
    counter = 0;
    println(tempo);
  } 

  if (key == 'r' || key == 'R'){
    reset();
  }
}

void next_current_col(){
  
  prev_col = current_col; 
  current_col++;
  if (current_col >= m) current_col = 0;
}

void update(){
  
  for(int i = 0; i < n; i++){
    buttons[prev_col][i].current = false;
    buttons[current_col][i].current = true;
    buttons[prev_col][i].update_and_display();
    buttons[current_col][i].update_and_display();
    
    if (buttons[current_col][i].on)
      sounds[i].play();
  }
}

void hover(){
  
  buttons[prev_i][prev_j].hovered = false;
  buttons[prev_i][prev_j].display();
  
  int i = mouseX / sz;
  int j = mouseY / sz; 
  
  if (i < m && j < n){   
    buttons[i][j].hovered = true; 
    buttons[i][j].display();
  }
  
  prev_i = i;
  prev_j = j;
}

void initialize_buttons(){
  
  buttons = new Button[m][n];
  
  for (int i = 0; i < m; i++){
    for(int j = 0; j < n; j++){
      buttons[i][j] = new Button(sz * i , sz * j, sz);
      buttons[i][j].display();
    } 
  }
}

void reset(){
  

  for (int i = 0; i < m; i++){
    for(int j = 0; j < n; j++){
      buttons[i][j].on = false;
      buttons[i][j].current = false;
      buttons[i][j].update_and_display();
    } 
  }
  
  current_col = 0; 
  prev_col = m - 1; 
  tempo = 10; 
}

void initialize_sounds(){
  
  sounds = new SoundFile[8];

  sounds[0] = new SoundFile(this, "soundbite0.mp3");
  sounds[1] = new SoundFile(this, "soundbite1.mp3");
  sounds[2] = new SoundFile(this, "soundbite2.mp3");
  sounds[3] = new SoundFile(this, "soundbite3.mp3");
  sounds[4] = new SoundFile(this, "soundbite4.mp3");
  sounds[5] = new SoundFile(this, "soundbite5.mp3");
  sounds[6] = new SoundFile(this, "soundbite6.mp3");
  sounds[7] = new SoundFile(this, "soundbite7.mp3");
}