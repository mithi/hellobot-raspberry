from gpiozero import MotionSensor
from robot_modules import Listener, Responder, Directive, get_response
from face_finder import FaceFinder
from relayer import Relayer
from time import sleep 
import os 

COUNTS = 10000
TRIGGER_WORD = "robot"
PIR_PIN = 26

listener = Listener()                  # listens to microphone and outputs text
responder = Responder()                # plays video on screen 
relayer = Relayer()                    # communicates to arduino
directive = Directive(TRIGGER_WORD)
pir = MotionSensor(PIR_PIN)
face_finder = FaceFinder()

def smart_camera():

  COUNT = 1000

  for _ in range(COUNT):
    face_finder.show()
  
  face_finder.shutdown()
  
def shutdown():
  SHUTDOWN = "sudo shutdown -h now"
  os.system(SHUTDOWN)
  
def obey(key):
  if key in ['forward', 'backward', 'left', 'right']: relayer.command(key)
  if key == 'death': shutdown()
  if key == 'camera': smart_camera()

def listen():
  relayer.signal("listening")
  phrase = listener.hear()
  relayer.signal("message decoded")
  return phrase

def reply(phrase):
  relayer.command("move arms")
  responder.show(get_response(phrase))        # plays the corresponding video given the video title 

def interact():
  phrase = listen()
  if phrase:
    key = directive.command(phrase)
    obey(key) if key else reply(phrase)

def greet():
  relayer.signal("move arms")
  responder.default()
  responder.wake()
  responder.greet()

###########################################################################################################

responder.default()               #shows default eye image on screen
relayer.connect()                 #connect to arduino port

while True:
  
  if pir.motion_detected:

    greet()
    print "person detected for the first time"

    while pir.motion_detected:
      interact()
      print "person still detected"

  responder.sleep()
  print "no person detected"


