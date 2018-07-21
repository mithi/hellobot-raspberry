# Alternative OOP style Library for Plumgeek's Ringo Robot 
Ringo is a cute robot bug by [PlumGeek](http://plumgeek.com) based on [Arduino](http://arduino.cc) launched in [Kickstarter](http://kickstarter.com) on March 2015. You can learn more about Ringo from their official website. This is an alternative library that you can use on the Ringo platform. 

# SAMPLE USAGE
```c
//include library
#include "Ringo.h"

//instantiate objects
Motors motor;
Communication communication;
LightSensors lightsensor;
Pixels pixel;

//enable communication via serial is disabled, motor is disabled
communication.Enable()

//enable light/line sensors, pixel lights are disabled
lightsensor.Enable()

//print analog readings of all three LIGHT sensors at the top of Ringo - reading range is 0 - 255
Serial.println("");
Serial.print("\t L: ");
Serial.print(lightsensor.Reading(TOP, LEFT));
Serial.print("\t R: ");
Serial.print(lightsensor.Reading(TOP, RIGHT));
Serial.print("\t D: ");
Serial.print(lightsensor.Reading(TOP, REAR));

//print analog readings of all three LINE sensors at the bottom of Ringo - reading range is 0 - 255
Serial.println("");
Serial.print("\t L: ");
Serial.print(lightsensor.Reading(BOTTOM, LEFT));
Serial.print("\t R: ");
Serial.print(lightsensor.Reading(BOTTOM, RIGHT));
Serial.print("\t D: ");
Serial.print(lightsensor.Reading(BOTTOM, REAR));
  
//enable motor, communication via seria
motor.Enable()

// drive forward, backward, then rotate right, rotate left
// note at driving forward and back won't be perfect because the motors aren't perfectly the same
motor.Drive(255, 255);
delay(500);
motor.Drive(-255, -255);
delay(500);
motor.Drive(255, -255);
delay(500);
motor.Drive(-255, 255);
delay(500);

//enable pixel lights, light sensors are disabled
pixel.Enable()

// don't turn all light with brightness of more than 100 
// for there is a risk of drawing more current than the battery can discharge
pixel.TopFront(0, 0, 100);
pixel.TopRear(0, 0, 100);
pixel.LeftEye(100, 0, 0);
pixel.RightEye(0, 100, 0);
pixel.BottomFront(0, 100, 100);
pixel.BottommRear(100, 0, 100);
```

# SETUP
Setting up Ringo is the same as in the official version: 
- http://www.plumgeek.com/ringo-getting-started.html

Which includes the following steps:
- Install the Arduino Development IDE 
- Install the USB Driver
- Inside Arduino, select "Arduino Pro or Pro Mini" as the board, select "ATMega328, 8MHz" as the processor
- Inside Arduino, Select the correct port in Tools > Port

# SETTING UP THE LIBRARIES 
Put the following folders in the 'Libraries' folder inside your  'Arduino' folder in your computer as detailed here:
- https://learn.adafruit.com/adafruit-all-about-arduino-libraries-install-use/how-to-install-a-library

The main libraries are the following: 
- Ringo 
- - https://github.com/mithi/ringo-basic/tree/master/libraries/Ringo
- Adafruit Neopixel Library
- - https://github.com/mithi/ringo-basic/tree/master/libraries/others/Adafruit_NeoPixel
- Turn Sensor 
- - https://github.com/mithi/ringo-basic/tree/master/libraries/TurnSensor
- L3G Gyro 
- - https://github.com/mithi/ringo-basic/tree/master/libraries/others/L3G
- Sparkfun Accelerometer
- - https://github.com/mithi/ringo-basic/tree/master/libraries/others/SparkFun_MMA8452Q_Accelerometer

# SAMPLE CODES

## Tests
In lines 19 - 23 comment out which module you'd want to test. The light and sensor sensor readings are displayed via serial. 
- https://github.com/mithi/ringo-basic/blob/master/examples/old-examples/other-tests/RingoTest/RingoTest.ino
```
void loop() {

  //motorTest();
  //topLightSensorTest();
  //bottomEdgeSensorTest();
  //piezoSweepTest();
  //pixelTest();  
}
```
Note that if you enable the motors you can't use the serial. If you use the light sensors at a particular time you can't use the pixels. They are controlled by the same pins. Enable them as you use them. When enabling one, the other is automatically disabled. 
```
  //motor.Enable();
  communication.Enable();

  lightsensor.Enable();
  //pixel.Enable();
```

## Fence
- https://github.com/mithi/ringo-basic/blob/master/examples/old-examples/other-tests/RingoFenceTest/RingoFenceTest.ino
- Running the code above should make Ringo move as in the video below: 
- https://www.youtube.com/watch?v=hBawKfUeksA

## Other Sample Codes
1. Print heading of Ringo based on Gyro via Serial
- https://github.com/mithi/ringo-basic/blob/master/examples/gyro-ringo-2/gyro-ringo-2.ino
2. Turn 90 degrees every half a second with PID control
- https://github.com/mithi/ringo-basic/blob/master/examples/gyro-ringo-3/gyro-ringo-3.ino
3. Light Following
- https://github.com/mithi/ringo-basic/blob/master/examples/old-examples/other-tests/RingoLineFollowing/RingoLightFollowing.ino
4. Print orientation of Ringo based on Acceleration via Serial
- https://github.com/mithi/ringo-basic/blob/master/examples/old-examples/accel-tests/RingAccel/RingAccel.ino

# VIDEOS AND IMAGES
- https://www.facebook.com/nanicalabs/videos/1668384973425772/
- https://www.youtube.com/watch?v=hBawKfUeksA
![image1](https://github.com/mithi/ringo-basic/blob/master/ringoIMG1.png)
![image2](https://github.com/mithi/ringo-basic/blob/master/ringoIMG2.png)
![image3](https://github.com/mithi/ringo-basic/blob/master/ringoIMG3.png)
