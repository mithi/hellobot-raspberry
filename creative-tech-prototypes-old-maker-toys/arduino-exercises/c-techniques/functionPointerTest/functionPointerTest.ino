
void apple(){
  Serial.println("apple");
}

void banana(){
  Serial.println("banana");
}

void coconut(){
  Serial.println("coconut");
}

void(*printFruit[])() = {apple, banana, coconut};  

void setup() {
  Serial.begin(115200); 
}

void loop() {
  int x = random(0, 3);
  printFruit[x]();   //(*printFruit[x])();
  delay(500);
}

