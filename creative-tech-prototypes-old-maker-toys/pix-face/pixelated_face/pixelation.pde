class Pixelation{
  
  int number_of_columns; 
  int number_of_rows;
  int cell_size; 
  int current_location; 
  int current_x; 
  int current_y; 
  int current_grey;
  int[][] pallete;
  color current_color;
  boolean inverted = false;
  
  Pixelation(int cs){
    pallete = pallete1;
    change_cell_size(cs);
  }
  
  void generate_location(int w, int i, int j){
    current_x = i*cell_size;
    current_y = j*cell_size;
    current_location = (w - current_x - 1) + current_y*w; //mirror image location of video's loaded pixels
  }
  
  void generate_grey(int c){
  
    float r = red(c);
    float g = green(c);
    float b = blue(c);
    current_grey = (int)((r + g + b)/ 3);    
  }
  
  void change_pallete(int[][] p){
    pallete = p; 
  }
  
  void change_cell_size(int cs){
    cell_size = cs;
    number_of_columns = width / cell_size; 
    number_of_rows = height / cell_size;  
  }
  
  void generate_color(){
    int [] p = {0, 0, 0};
    
    if (inverted){
      current_grey = 255 - current_grey; 
    }
    
    int n = current_grey / 35; // 255/ 35 = about 7
    p = pallete[n];
    current_color = color(p[0], p[1], p[2]);
  }
  
  void display(){
    pushMatrix();
    translate(current_x + cell_size/2, current_y + cell_size/2);
    rectMode(CENTER);
    fill(current_color);
    noStroke();
    rect(0, 0, cell_size, cell_size);
    popMatrix();
  }
}