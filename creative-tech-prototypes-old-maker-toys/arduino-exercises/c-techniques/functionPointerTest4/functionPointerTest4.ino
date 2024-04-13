
typedef int (*arithmeticOperation)(int a, int b);

int multiply(int a, int b){
  return a*b;
}

int subtract(int a, int b){
  return a-b;
}

int add(int a, int b){
  return a+b;
}

void printResult(int x, int y, arithmeticOperation result){
  Serial.println(result(x, y));
}

void setup(){

  Serial.begin(115200);

  int x = 15;
  int y = 8;

  arithmeticOperation result;

  result = multiply;
  Serial.println(result(x,y));
  result = add;
  Serial.println(result(x,y));
  result = subtract;
  Serial.println(result(x,y));
  
  printResult(x, y, multiply);
  printResult(x, y, add);
  printResult(x, y, subtract);

  arithmeticOperation operation[] = {multiply, add, subtract};
  Serial.println(operation[0](x,y));
  Serial.println(operation[1](x,y));
  Serial.println(operation[2](x,y));
}

void loop(){}
