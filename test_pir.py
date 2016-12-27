
from gpiozero import MotionSensor


PIR_PIN = 40
pir = MotionSensor(PIR_PIN)
responder = Responder()

responder.default_eye()

while True:

  if pir.motion_detected(): responder.greet()


