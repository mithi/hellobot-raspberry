from gpiozero import MotionSensor
from robot_modules import Listener, Responder, Relayer, Directive
from face_finder import FaceFinder
from helper import get_response

##################################################################################

COUNTS = 1000
TRIGGER_WORD = "super"
PIR_PIN = 40

directive = Directive(TRIGGER_WORD)
face_finder = FaceFinder()
pir = MotionSensor(PIR_PIN)
listener = Listener()    # listens to microphone and outputs text
responder = Responder()  # plays video on screen 
relayer = Relayer()      # communicates commands to arduino, gets feedback from arduino

##################################################################################

def obey(key):
  
  if key in ['forward', 'left', 'right']: smart_move(key)
  if key == 'camera': smart_camera()

def smart_camera():

  face_finder.start()

  for _ in range(0, COUNTS):

    face_finder.run()
    face_finder.show()
    
    phrase = listen()

    if "cheese" in phrase:
      face_finder.run()
      face_finder.save() #post on twitter?
      break  

def smart_move(key):

  relayer.command(key) 
  face_finder.start()
  
  for _ in range(0, COUNTS):

    face_finder.run()
    face_finder.show()

    if relayer.answer("obstacle?"):
      responder.show("obstacle_detected")
      break

def listen():

  relayer.signal("listening")
  phrase = listener.hear()
  relayer.signal("message decoded")
  return phrase

def reply(phrase):
  
  relayer.command("move arms")
  response = get_response(phrase) # picks one of several appropriate responses (video title) based on whether keyword is contained on the given phrase 
  responder.show(response)        # plays the corresponding video given the title of the video 

##################################################################################

responder.default()               #shows default eye image on screen

while True:

  if pir.motion_detected(): responder.greet()

  phrase = listen()
  if not phrase: continue

  key = directive.command(phrase)
  obey(key) if key else reply(phrase)

