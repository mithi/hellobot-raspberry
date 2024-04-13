enum velocity_measure{MILES_PER_HOUR, MM_PER_SEC, MM_PER_SEC_NEGATIVE};
 
union velocity{
  float miles_per_hour;
  unsigned long millimeters_per_second;
  long reverse_millimeters_per_second;
};

struct car_velocity{
  enum velocity_measure unit_of_measurement;
  union velocity value;
};

void display_car_velocity(struct car_velocity velocity){
  
  switch(velocity.unit_of_measurement){
    case MILES_PER_HOUR:
      Serial.print("miles per hour:");
      Serial.println(velocity.value.miles_per_hour);
      break;
    case MM_PER_SEC:
      Serial.print("millimeters per second (magnitude):");
      Serial.println(velocity.value.millimeters_per_second);
      break;
    case MM_PER_SEC_NEGATIVE:
      Serial.print("millimeters per second (moving backward):");
      Serial.println(velocity.value.reverse_millimeters_per_second);
      break;
    default:
      Serial.println("i don't know");
  }  
}

struct car_velocity my_velocity;

void setup() {
  
  Serial.begin(115200);
  my_velocity.unit_of_measurement = MILES_PER_HOUR;
  my_velocity.value.miles_per_hour  = 3.1;
  display_car_velocity(my_velocity);

  my_velocity.unit_of_measurement = MM_PER_SEC;
  my_velocity.value.millimeters_per_second = 400000;
  display_car_velocity(my_velocity);

  my_velocity.unit_of_measurement = MM_PER_SEC_NEGATIVE;
  my_velocity.value.reverse_millimeters_per_second = -200000;
  display_car_velocity(my_velocity);  
}

void loop() {
}
