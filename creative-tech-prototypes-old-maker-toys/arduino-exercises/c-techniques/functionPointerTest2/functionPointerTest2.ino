int apple(int c, int d){
  Serial.print(" apple(s) - ");
  return c + d;
}

int banana(int c, int d){
  Serial.print(" banana(s) - ");
  return c*d;
}

int coconut(int c, int d){
  Serial.print(" carrot(s) - ");
  return 2*c+d;
}

int(*fruitQuantity[])(int c, int d) = {apple, banana, coconut};  

void setup() {
  Serial.begin(115200); 
}

void loop() {
  int x = random(0, 3);
  int n = random(0, 10);
  int m = random(0, 10);
  
  int h = fruitQuantity[x](n, m);   //int h = (*fruitQuantity[x])(n, m);

  Serial.println(h);
  delay(500);
}


