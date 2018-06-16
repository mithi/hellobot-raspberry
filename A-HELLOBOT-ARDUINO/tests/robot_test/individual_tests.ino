void pixel_test(){
  
  for(int i=0;i<NUMBER_OF_PIXELS;i++){
    pixels.setPixelColor(i, pixels.Color(0,150,0)); 
    pixels.show(); 
    delay(50); 
  }
}

void pixel_animation_test(){
  int WAIT = 10;
  int half_sec = 500;

  colorWipe(pixels.Color(127, 255, 0), 2*WAIT);
  delay(half_sec);

  rainbow(WAIT);
  delay(half_sec);

  rainbowCycle(WAIT);
  delay(half_sec);

  theaterChase(pixels.Color(127, 0, 127), 2*WAIT);
  delay(half_sec);

  theaterChaseRainbow(WAIT);
  delay(half_sec);

  twelve_seconds();
  delay(half_sec);

  neopixel_animation2();
  delay(half_sec);

  neopixel_animation1();
  delay(half_sec);
}

void arms_test(){

  left_arm.write(MAX_ANGLE);
  delay(WAIT_TIME);

  left_arm.write(MIN_ANGLE);
  delay(WAIT_TIME);

  left_arm.write(DEFAULT_ANGLE);
  delay(WAIT_TIME);

  right_arm.write(MAX_ANGLE);
  delay(WAIT_TIME);

  right_arm.write(MIN_ANGLE);
  delay(WAIT_TIME);

  right_arm.write(DEFAULT_ANGLE);
  delay(WAIT_TIME);
}

void individual_motor_test(){

  //front right forward
  //motors.drive(PIN_MOTOR_DIRECTION_RIGHT_FRONT, PIN_MOTOR_SPEED_RIGHT_FRONT, SPEED, FORWARD);
  //delay(WAIT_TIME);
  //motors.drive(PIN_MOTOR_DIRECTION_RIGHT_FRONT, PIN_MOTOR_SPEED_RIGHT_FRONT, 0, 0);
  //delay(WAIT_TIME);
  
  //front right reverse
  //motors.drive(PIN_MOTOR_DIRECTION_RIGHT_FRONT, PIN_MOTOR_SPEED_RIGHT_FRONT, SPEED, REVERSE);
  //delay(WAIT_TIME);
  //motors.drive(PIN_MOTOR_DIRECTION_RIGHT_FRONT, PIN_MOTOR_SPEED_RIGHT_FRONT, 0, 0);
  //delay(WAIT_TIME);

  //front left forward
  //motors.drive(PIN_MOTOR_DIRECTION_LEFT_FRONT, PIN_MOTOR_SPEED_LEFT_FRONT, SPEED, FORWARD);
  //delay(WAIT_TIME);
  //motors.drive(PIN_MOTOR_DIRECTION_LEFT_FRONT, PIN_MOTOR_SPEED_LEFT_FRONT, 0, 0);
  //delay(WAIT_TIME);

  //front left reverse
  //motors.drive(PIN_MOTOR_DIRECTION_LEFT_FRONT, PIN_MOTOR_SPEED_LEFT_FRONT, SPEED, REVERSE);
  //delay(WAIT_TIME);
  //motors.drive(PIN_MOTOR_DIRECTION_LEFT_FRONT, PIN_MOTOR_SPEED_LEFT_FRONT, 0, 0);
  //delay(WAIT_TIME);

  //back right forward
  //motors.drive(PIN_MOTOR_DIRECTION_RIGHT_BACK, PIN_MOTOR_SPEED_RIGHT_BACK, SPEED, FORWARD);
  //delay(WAIT_TIME);
  // motors.drive(PIN_MOTOR_DIRECTION_RIGHT_BACK, PIN_MOTOR_SPEED_RIGHT_BACK, 0, 0);
  //delay(WAIT_TIME);

  //back right reverse
  //motors.drive(PIN_MOTOR_DIRECTION_RIGHT_BACK, PIN_MOTOR_SPEED_RIGHT_BACK, SPEED, REVERSE);
  //delay(WAIT_TIME);
  //motors.drive(PIN_MOTOR_DIRECTION_RIGHT_BACK, PIN_MOTOR_SPEED_RIGHT_BACK, 0, 0);
  //delay(WAIT_TIME);


  //back left forward
  //motors.drive(PIN_MOTOR_DIRECTION_LEFT_BACK, PIN_MOTOR_SPEED_LEFT_BACK, SPEED, FORWARD);
  //delay(WAIT_TIME);
  //motors.drive(PIN_MOTOR_DIRECTION_LEFT_BACK, PIN_MOTOR_SPEED_LEFT_BACK, 0, 0);
  //delay(WAIT_TIME);

  // back left reverse
  motors.drive(PIN_MOTOR_DIRECTION_LEFT_BACK, PIN_MOTOR_SPEED_LEFT_BACK, SPEED, REVERSE);
  delay(WAIT_TIME);
  motors.drive(PIN_MOTOR_DIRECTION_LEFT_BACK, PIN_MOTOR_SPEED_LEFT_BACK, 0, 0);
  delay(WAIT_TIME);

}

void movement_test() {
  int WAIT_TIME = 5000;
  
  //forward
  motors.move(SPEED, FORWARD);
  delay(WAIT_TIME);
  motors.move(0, 0);
  delay(WAIT_TIME);

  //reverse
  motors.move(SPEED, REVERSE);
  delay(WAIT_TIME);
  motors.move(0, 0);
  delay(WAIT_TIME);

  //turn left
  motors.rotate(LEFT_TURNING_SPEED, LEFT_TURNING_SPEED, FORWARD, REVERSE);
  delay(WAIT_TIME);
  motors.move(0, 0);
  delay(WAIT_TIME);

  //turn right
  motors.rotate(LEFT_TURNING_SPEED, RIGHT_TURNING_SPEED, REVERSE, FORWARD);
  delay(WAIT_TIME);
  motors.move(0, 0);
  delay(WAIT_TIME);
}


