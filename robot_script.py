from gpiozero import MotionSensor
from robot_modules import Listener, Responder, Directive, get_response
from face_finder import FaceFinder
from relayer import Relayer
from time import sleep 

COUNTS = 10000
TRIGGER_WORD = "super"
PIR_PIN = 26

pir = MotionSensor(PIR_PIN)
listener = Listener()      # listens to microphone and outputs text
responder = Responder()    # plays video on screen 
relayer = Relayer()        # communicates to arduino
directive = Directive(TRIGGER_WORD)
face_finder = FaceFinder()

def move(key):
  relayer.command(key) 

def obey(key):
  if key in ['forward', 'backward', 'left', 'right']: move(key)
  if key == 'death': responder.shutdown()
  if key == 'camera': robot_camera()


def robot_camera():

  COUNT = 1000

  for _ in range(COUNT):
    face_finder.show()
  
  face_finder.shutdown()


def listen():

  relayer.signal("listening")
  phrase = listener.hear()
  relayer.signal("message decoded")
  return phrase

def reply(phrase):
  
  relayer.command("move arms")
  response = get_response(phrase) # picks one of several appropriate responses (video title) 
                                  # based on whether the given phrase contains a specific keyword 
  responder.show(response)        # plays the corresponding video given the video title 

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
face_finder.shutdown()

while True:
  
  if pir.motion_detected:

    greet()

    while pir.motion_detected:
      interact()

  responder.sleep()  

