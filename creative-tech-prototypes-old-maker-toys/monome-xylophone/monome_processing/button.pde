color on_color = #258EA6;
color on_current_color = #7EBC89;
color off_color = #E2C2FF;
color off_current_color = #549F93;
int margin = 5;

class Button {
  int x, y, s; //x-coordinate, y-coordinate, side-length
  boolean hovered = false;
  boolean on = false;
  boolean current = false;
  int state = 2; 
  color state_color[] = {on_color, on_current_color, off_color, off_current_color};
  
  Button(int _x, int _y, int _s){
    x = _x + margin; 
    y = _y + margin;
    s = _s - 2*margin;
  }
  
  void update_and_display(){
    update();
    display();
  }
  
  void display(){
    
    if (hovered){
      stroke(#80727B);
    } else {
      stroke(255);
    }
    
    fill(state_color[state]);    
    rect(x, y, s, s);
  }
  
  void update(){
    if(on){
      state = 0;
      if(current) state = 1;
    } else {
      state = 2;
      if(current) state = 3; 
    }
  }
}