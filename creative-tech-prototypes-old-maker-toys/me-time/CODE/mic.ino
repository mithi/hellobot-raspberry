#define DC_OFFSET 0

int microphone_reading(){

  int n = analogRead(MIC_PIN); // raw reading
  int x = (n - 512 - DC_OFFSET);
  n =  x > 0 ? x : 0;  // center on zero 
  n = (n <= NOISE) ? 0 : (n - NOISE);  //take out noise
  return n;
}

int average_microphone_reading(){
  int number_of_readings = 10;
  int sum_of_readings = 0;
  
  for (int x = 0; x < number_of_readings; x++)
    sum_of_readings += microphone_reading();

  return sum_of_readings / number_of_readings;
}
