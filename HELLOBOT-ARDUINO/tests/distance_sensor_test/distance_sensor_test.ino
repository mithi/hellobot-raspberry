#include "robot.h"

DistanceSensor center_distance, left_distance, right_distance;

void setup() {
  Serial.begin(9600);
  enable_distance_detection();
  right_distance.attach(PIN_DISTANCE_SENSOR_RIGHT);
  center_distance.attach(PIN_DISTANCE_SENSOR_CENTER);
  left_distance.attach(PIN_DISTANCE_SENSOR_LEFT);

}

void loop() {
  Serial.print(left_distance.obstacle_detected());
  Serial.print(" ");
  Serial.print(center_distance.obstacle_detected());
  Serial.print(" ");
  Serial.print(right_distance.obstacle_detected());
  Serial.println(" ");
  delay(100);
}
