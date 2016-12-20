
from gpiozero import MotionSensor
from robot_modules import Responder, Listener
from time import sleep

PIR_PIN = 26
pir = MotionSensor(PIR_PIN)
responder = Responder()
listener = Listener()

responder.default()

while True:

  if pir.motion_detected: 
    responder.greet()
    while pir.motion_detected:
      print listener.hear()


