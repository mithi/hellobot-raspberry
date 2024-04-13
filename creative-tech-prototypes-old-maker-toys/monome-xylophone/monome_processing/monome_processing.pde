import processing.sound.*;
import processing.serial.*;

Serial my_port;
String val; 

int n = 8; //number of rows
int m = 26; // number of cols
int sz = 25; //size of button
int incr = 1; // increment tempo
int min_tempo = 2;   // minimum tempo
int max_tempo = 25;  // maximum tempo 

int tempo = 20;
int counter = 0; 
int prev_i; 
int prev_j; 
int current_col = 0; 
int prev_col = m - 1; 

Button[][] buttons;

void setup(){
  
  size(650, 200); // sz*m, sz*n
  background(255);
  initialize_buttons();
  
  String port_name = Serial.list()[1];
  my_port = new Serial(this, port_name, 115200);
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
  int val = 0; 
  
  for(int i = 0; i < n; i++){
    buttons[prev_col][i].current = false;
    buttons[current_col][i].current = true;
    buttons[prev_col][i].update_and_display();
    buttons[current_col][i].update_and_display();
    
    if (buttons[current_col][i].on)
      val = val | (1 << i) ;
  }
  my_port.write(char(val));
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