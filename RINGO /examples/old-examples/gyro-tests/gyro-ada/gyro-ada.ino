#include <Wire.h> 
#include <Adafruit_L3GD20.h>


// The default constructor uses I2C
Adafruit_L3GD20 gyro;

void setup() 
{
  Serial.begin(9600);
  
  // Try to initialise and warn if we couldn't detect the chip
   if (!gyro.begin(gyro.L3DS20_RANGE_2000DPS))
  //if (!gyro.begin(gyro.L3DS20_RANGE_500DPS))
  //if (!gyro.begin(gyro.L3DS20_RANGE_250DPS))
  {
    Serial.println("Oops ... unable to initialize the L3GD20. Check your wiring!");
    while (1);
  }
}

void loop() 
{
  gyro.read();
  Serial.print("X: "); Serial.print((int)gyro.data.x);   Serial.print(" ");
  Serial.print("Y: "); Serial.print((int)gyro.data.y);   Serial.print(" ");
  Serial.print("Z: "); Serial.println((int)gyro.data.z); Serial.print(" ");
  delay(100);
}
