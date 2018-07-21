These scripts are the result of my work for visual artist Daniel Slattnes. 
The goal is to make the mounted plant 'control' the hexapod robot. 
In other words, the movements done by the hexapod robot is based on the 
signals from the plant's leaves. 

# Videos
- https://youtu.be/9wri8Cr78Lo
- https://youtu.be/Dt8aBi2poVQ

Here is Daniel Stattnes's personal website:
- http://slaattnes.com/

![plantoid](https://github.com/mithi/stubby/blob/master/plantoid.jpg)


### The scripts make use of the following open-source libraries:
- https://github.com/mithi/hexy/
- Modifications to `core.py`: https://github.com/slaattnes/hexy/
- https://github.com/adafruit/Adafruit_Python_ADS1x15/
- https://github.com/adafruit/Adafruit_Python_PCA9685/

### The hexapod is a modified version of an open-source hexapod called Stubby.
Stubby's physical frame has been modified by Daniel Slattness to use standard-sized MG995 servos instead of the 9-gram micro-sized servos used in the original design.
- http://stubby.digitalcave.ca/stubby/

### Main Electronics and Actuators:
- 1x Raspberry Pi Zero 
- - https://www.raspberrypi.org/products/raspberry-pi-zero/
- 2x PWM Drivers (PCA9685) 
- - https://learn.adafruit.com/adafruit-16-channel-servo-driver-with-raspberry-pi
- 1x ADC with PGA (ADS1115)
- - https://learn.adafruit.com/adafruit-4-channel-adc-breakouts
- 18x Servos (Towerpro MG995)
- - https://towerpro.com.tw/product/mg995/

![plantoid WIP](https://github.com/mithi/stubby/blob/master/wip_plantoid.jpg)
