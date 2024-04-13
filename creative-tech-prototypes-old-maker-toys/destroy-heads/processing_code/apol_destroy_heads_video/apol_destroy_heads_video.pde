import processing.video.*;
import processing.serial.*;

Serial my_port; 
String val, port_name;
AnalogReadings potentiometers;
int values[] = {2, 0, 0, 0, 75, 0, 0, 0};

Movie video;

float shape_factors[] = {0.5, 0.75, 1.0, 1.25, 1.5, 1.75, 2};
float rotation_factors[]= {0, 0.25, 0.33, 0.5, 0.66, 0.75, 1, 1.5, 2, 3, 4};
float rotate_constant = 2*PI / 255.0;

//independent variables
int cell_size = 20;
int alpha = 75;
int rotate_factor = 0;
int width_factor = 3;
int height_factor = 3;
int pallete_counter = 0;
boolean shape = false;
boolean inverted = false;

//dependent variables
int half_cell_size;
int shape_width;
int shape_height;
int cols, rows; 
float angle; 

void setup(){
  
  size(540, 720);
  rectMode(CENTER);
  frameRate(30);
  pixelDensity(2);
  colorMode(RGB, 255, 255, 255, 100);
  
  update_dependent_variables();
  
  video = new Movie(this, "x.mov");
  video.loop();  

  update_dependent_variables();

  port_name = Serial.list()[1];
  my_port = new Serial(this, port_name, 250000);
  potentiometers = new AnalogReadings(my_port);
  
}


void draw(){
  
  update_analog_readings();
  
  if(video.available()){
    video.read();
    video.loadPixels();
    background(255);
    generate_picture();
  }
}

void generate_picture(){
  for(int i = 0; i < cols; i++){
    for(int j = 0; j < rows; j++){
      
      int x = i*cell_size;
      int y = j*cell_size;
      
      color c = video.get(x, y);
      
      int current_grey = int((red(c)+ green(c) + blue(c))/3);
      
      if(inverted){
        current_grey = 255 - current_grey;
      }
      
      int g =int(map(current_grey, 0, 255, 0, 7));
      int[][] p = palletes[pallete_counter];
      
      color nc = color(p[g][0], p[g][1], p[g][2], alpha);
      
      pushMatrix();
      translate( x + half_cell_size, y + half_cell_size);
      rotate(int(angle * brightness(c)));
      noStroke();
      fill(nc);
      
      if(shape){
        rect(0, 0, shape_width, shape_height);
      }else{
        ellipse(0, 0, shape_width, shape_height);
      }
      
      popMatrix();  
    }
  }
}

void update_analog_readings(){
  
  potentiometers.update();
  values = potentiometers.get_values();
  
  cell_size = values[0];
  width_factor = values[1];
  height_factor = values[2];
  rotate_factor = values[3];
  alpha = values[4];  
  pallete_counter = values[5];
  shape = boolean(values[6]);
  inverted = boolean(values[7]);
  
  update_dependent_variables();
}

void update_dependent_variables(){
  
 half_cell_size = cell_size / 2;
 shape_width = int(shape_factors[width_factor]*cell_size);
 shape_height = int(shape_factors[height_factor]*cell_size);
 angle = rotate_constant*rotation_factors[rotate_factor]; 
 cols = width / cell_size;
 rows = height / cell_size;
}