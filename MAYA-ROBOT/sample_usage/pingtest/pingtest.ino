#include "PROTO3.h"

Ping ping; 
void setup() {
  ping.enable();
  Serial.begin(9600);
}

void loop() {
  Serial.print(" cm: ");
  Serial.print(ping.centimeters());
  Serial.print(" inches: ");
  Serial.println(ping.inches());
  delay(500);
}
