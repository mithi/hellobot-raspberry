#include "PROTO3.h"

Pixels pixels; 

void setup() {
  pixels.enable();
}

void loop() {
 pixels.color(LEFT_MOST_PIX, BLUE); 
 pixels.color(LEFT_CENTER_PIX, ORANGE);
 pixels.color(RIGHT_CENTER_PIX, PINK);
 pixels.color(RIGHT_MOST_PIX, LIME);
 delay(500);
 pixels.left_most(5, 5, 5);
 pixels.left_center(25, 25, 25);
 pixels.right_center(50, 50, 150);
 pixels.right_most(100, 100, 100);
 delay(500);
}
