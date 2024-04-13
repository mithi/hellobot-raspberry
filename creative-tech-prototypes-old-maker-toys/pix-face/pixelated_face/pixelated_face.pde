import processing.video.*;

int pallete_counter = 0;
int cell_counter = 0;
int[] cell_sizes = {1, 2, 3, 5, 8, 10, 15, 20};

Pixelation pix; 
Capture video;

void setup() {
  
  println(palletes.length);
  size(640, 480);
  frameRate(30);
  background(0);
  colorMode(RGB, 255, 255, 255, 100);
  
  video = new Capture(this, width, height);
  video.start();  

  pix = new Pixelation(cell_sizes[0]); 
}

void draw() { 
  
  if (video.available()) {
    video.read();
    video.loadPixels();
  }
  
  for (int i = 0; i < pix.number_of_columns; i++) {
    for (int j = 0; j < pix.number_of_rows; j++) {
      
      pix.generate_location(video.width, i, j); 
      pix.generate_grey(video.pixels[pix.current_location]);
      pix.generate_color();
      pix.display();
    }
  }
}

void keyPressed(){
  if(key == 'q'){
    pallete_counter++;
    pallete_counter %=  palletes.length;
    pix.change_pallete(palletes[pallete_counter]);
    println(pallete_counter);
  }
  
  if(key == 'w'){
     cell_counter++;
     cell_counter %= cell_sizes.length;
     pix.change_cell_size(cell_sizes[cell_counter]);
  }
  
  if(key == 'e'){
    pix.inverted = !pix.inverted;
  }
}