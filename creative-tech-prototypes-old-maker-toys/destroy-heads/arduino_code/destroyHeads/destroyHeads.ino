const int button1 = 5;
const int button2 = 6;

void setup() {
  Serial.begin(250000);
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
}

void loop() {
  Serial.print(map(analogRead(A0), 0, 1023, 2, 24));
  Serial.print(",");
  Serial.print(map(analogRead(A1), 0, 1023, 0, 6));
  Serial.print(",");
  Serial.print(map(analogRead(A2), 0, 1023, 0, 6));
  Serial.print(",");
  Serial.print(map(analogRead(A3), 0, 1023, 0, 10));
  Serial.print(",");
  Serial.print(map(analogRead(A4), 0, 1023, 30, 100));
  Serial.print(",");
  Serial.print(map(analogRead(A5), 0, 1023, 0, 27));
  Serial.print(",");
  Serial.print(digitalRead(button1));
  Serial.print(",");
  Serial.print(digitalRead(button2));
  Serial.println(",");
  delay(200);
}
