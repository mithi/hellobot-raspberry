long longVar = 99;
long *pointer;
long *anotherPointer;
long var[3];
char charVar = 'M';
  
void setup() {

  Serial.begin(115200);

  var[0] = 5;
  pointer = var;
  anotherPointer = pointer;
  *(anotherPointer+1) = 20;
  *(pointer+2) = 50;
 
  Serial.println("*****************************************");

  Serial.print("var[0]: "); 
  Serial.println(var[0]);

  Serial.print("*pointer: "); //value
  Serial.println(*pointer);

  Serial.print("*anotherPointer: ");
  Serial.println(*anotherPointer);

  Serial.println("*****************************************");

  Serial.print("var[1]: ");
  Serial.println(var[1]);

  Serial.print("*(pointer+1): ");
  Serial.println(*(pointer+1));
  
  Serial.print("*(anotherPointer+1): ");
  Serial.println(*(anotherPointer+1));

  Serial.println("*****************************************");

  Serial.print("var[2]: ");
  Serial.println(var[2]);

  Serial.print("*(pointer+2): ");
  Serial.println(*(pointer+2));

  Serial.print("*(anotherPointer+2): ");
  Serial.println(*(anotherPointer+2));

  Serial.println("*****************************************");

  Serial.print("&var: ");  // address
  Serial.println(long(&var));

  Serial.print("pointer: ");
  Serial.println(long(pointer));

  Serial.print("anotherPointer: ");
  Serial.println(long(anotherPointer));

  Serial.println("*****************************************");

  Serial.print("var+1: "); // address of var 1  + size of data type (long is bytes)
  Serial.println(long(var+1));

  Serial.print("pointer+1: "); // value of pointer (which is the address of var 1) + size of data type (long is bytes)
  Serial.println(long(pointer+1));

  Serial.print("anotherPointer+1: ");
  Serial.println(long(anotherPointer+1));

  Serial.println("*****************************************");

  Serial.print("var+2: ");
  Serial.println(long(var+2));

  Serial.print("pointer+2: ");
  Serial.println(long(pointer+2));

  Serial.print("anotherPointer+2: ");
  Serial.println(long(anotherPointer+2));

  Serial.println("*****************************************");

  Serial.print("&pointer: ");                                   
  Serial.println(long(&pointer));

  Serial.print("&pointer + 1: "); // address + size of data type (pointer is 2 bytes)
  Serial.println(long(&pointer + 1));

  Serial.print("&anotherPointer: ");
  Serial.println(long(&anotherPointer));

  Serial.print("&anotherPointer + 1: ");
  Serial.println(long(&anotherPointer + 1));

  Serial.println("*****************************************");

  Serial.print("longVar: "); // value
  Serial.println(longVar);

  Serial.print("&longVar: "); // address
  Serial.println(long(&longVar));

  Serial.print("&longVar + 1: ");  // address + size of data type (long is 4 bytes)
  Serial.println(long(&longVar + 1));

  Serial.println("*****************************************");

  Serial.print("charVar: "); // value
  Serial.println(charVar);

  Serial.print("&charVar: "); // address
  Serial.println(long(&charVar));

  Serial.print("&charVar + 1: "); // address + size of data type (char is 1 byte)
  Serial.println(long(&charVar + 1));

}

void loop() {
}
