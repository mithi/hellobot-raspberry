import RPi.GPIO as GPIO
from robot_modules import Listener, Responder, Directive, get_response
from face_finder import FaceFinder
from relayer import Relayer
from time import sleep 
import os
import sys

TRIGGER_WORD = "robot"
directive = Directive(TRIGGER_WORD)

listener = Listener()                  # listens to microphone and outputs text
responder = Responder()                # plays video on screen 
relayer = Relayer()                    # communicates to arduino

PIR_PIN = 26
GPIO.setmode(GPIO.BCM)
GPIO.setup(PIR_PIN, GPIO.IN)

def stop_camera():
  try:
    os.system("/home/pi/RPi_Cam_Web_Interface/stop.sh")
  except:
    pass

def smart_camera():
  COUNT = 50
  face_finder = FaceFinder()
  for _ in range(COUNT):
    face_finder.show()
  face_finder.shutdown()
  responder.default()
  
def obey(key):
  if key in ['forward', 'back', 'left', 'right']: relayer.command(key)
  if key == 'death': os.system("sudo shutdown -h now")
  if key == 'camera': smart_camera()

def listen():
  relayer.signal("listening")
  phrase = listener.hear()
  relayer.signal("message decoded")
  return phrase

def reply(key):
  relayer.command("move arms")
  responder.show(key)

def interact():
  phrase = listen()
  if phrase:
    key = directive.command(phrase)
    obey(key) if key else reply(get_response(phrase))

def greet():
  relayer.signal("move arms")
  responder.default()
  responder.wake()
  responder.greet()

############################################################
def cleanup():
  print "quitting..."
  GPIO.cleanup()
  relayer.signal("message decoded")
  responder.sleep()
  stop_camera()
  sys.exit()
      
def main():
  
  if GPIO.input(PIR_PIN):
    print "person detected for the first time"
    greet()

    for x in range(20):
      print "count", x
      interact()

  responder.sleep()
  print "no person detected"
  sleep(1)

if __name__ == '__main__':
  
  responder.default()               #shows default eye image on screen
  relayer.connect()                 #connect to arduino port
  stop_camera()
  
  while True:
    try:
      main()
    except KeyboardInterrupt:
      cleanup()

