from gpiozero import MotionSensor
from robot_modules import Listener, Responder, Directive, get_response
from face_finder import FaceFinder
from relayer import Relayer

COUNTS = 10000
TRIGGER_WORD = "super"
PIR_PIN = 40

pir = MotionSensor(PIR_PIN)
listener = Listener()      # listens to microphone and outputs text
responder = Responder()    # plays video on screen 
relayer = Relayer()        # communicates to arduino

def smart_move(key):

  relayer.command(key) 
  face_finder = FaceFinder()
  
  for _ in range(0, COUNTS):
    if face_finder.face_detected(): relayer.command("move arms")
    face_finder.show(update = False)

def obey(key):
  if key in ['forward', 'reverse', 'left', 'right']: smart_move(key)

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

###########################################################################################################

responder.default()               #shows default eye image on screen
responder.black()

while True:

  if pir.motion_detected(): responder.greet()

  phrase = listen()
  if not phrase: continue

  key = directive.command(phrase)
  obey(key) if key else reply(phrase)
