from gpiozero import MotionSensor

PIR_PIN = 26
pir = MotionSensor(PIR_PIN)

while True:

  if pir.motion_detected:
    print "motion detected"
    while pir.motion_detected:
      print "motion still detected"
  else:
    print "no motion!"
   
