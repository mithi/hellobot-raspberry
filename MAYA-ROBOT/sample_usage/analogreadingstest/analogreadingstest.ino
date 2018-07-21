#include "PROTO3.h"

AnalogReadings line_sensor, light_sensor; 

void setup() {
  line_sensor.enable(PIN_LINE_LEFT, PIN_LINE_RIGHT);
  light_sensor.enable(PIN_LIGHT_LEFT, PIN_LIGHT_RIGHT);
  Serial.begin(9600);
}

void loop() {

  Serial.print(" | line left: ");
  Serial.print(line_sensor.left());
  Serial.print(" | line right: ");
  Serial.print(line_sensor.right());
  Serial.print(" | light left: ");
  Serial.print(light_sensor.left());
  Serial.print(" | light right: ");
  Serial.println(light_sensor.right());

  delay(1000);
}
