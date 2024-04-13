char display_message[200]; 
int current_left_speed; 
int current_right_speed;


typedef void (*carMotion)(int);

void moveCar(int speed_magnitude, carMotion motion){      // void (*carMotion)(int) <----> carMotion motion 
  motion(speed_magnitude); //(*motion)(speed_magnitude);
  sprintf(display_message, "left speed: %d  right speed: %d \n", current_left_speed, current_right_speed);
  Serial.println(display_message);
 
}

void forward(int my_speed){
  Serial.println("Moving Forward:");
  speeds(my_speed, my_speed);
}

void backward(int my_speed){
  Serial.println("Moving backward:");
  speeds(-my_speed, -my_speed);
}

void rotateCCW(int my_speed){
  Serial.println("Rotating counterclockwise:");
  speeds(-my_speed, my_speed);
}

void rotateCW(int my_speed){
  Serial.println("Rotating clockwise:");
  speeds(my_speed, -my_speed);
}

void speeds(int left_speed, int right_speed){
  current_left_speed = left_speed;
  current_right_speed = right_speed;
}

void setup() {
  Serial.begin(115200);
  moveCar(5, forward);
  moveCar(20, backward);
  moveCar(78, rotateCW);
  moveCar(100, rotateCCW);
}

void loop() {
}
