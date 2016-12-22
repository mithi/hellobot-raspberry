from gpiozero import MotionSensor
from robot_modules import Listener, Responder, Relayer, Directive
from face_finder import FaceFinder
from helper import get_response

##################################################################################

TRIGGER_WORD = "super"
PIR_PIN = 40

directive = Directive(TRIGGER_WORD)
face_finder = FaceFinder()
pir = MotionSensor(PIR_PIN)
listener = Listener()    # listens to microphone and outputs text
responder = Responder()  # plays video on screen 
relayer = Relayer()      # communicates commands to arduino, gets feedback from arduino

##################################################################################

def obey_mode(key):
  
  if key in ['forward', 'left', 'right']:
    smart_move(key)
  
  if key == 'camera': 
    smart_camera()

def smart_camera():

  COUNTS = 1000

  face_finder.start()
  
  relayer.signal()

  for _ in range(0, COUNTS):
    face_finder.run()
    face_finder.show()
    
    relayer.signal("listening")
    phrase = listener.hear()
    relayer.signal("message decoded")

    if "stop" in phrase:
      break
    if "cheese" in phrase:
      face_finder.run()
      face_finder.save()
      break  

def smart_move(key):
  
  relayer.signal("moving")
  relayer.smart_move(key)
  
  face_finder.start()
  
  while True:

    face_finder.run()
    face_finder.show()

    if face_finder.has_faces()
      responder.greet()
      break

    if relayer.answer("obstacle?"):
      relayer.signal("move arms")
      responder.express("obstacle_detected")
      break

    if relayer.answer("complete?")
      relayer.signal("move arms")
      responder.express("finished_directive")
      break

def reply(phrase):
  
  relayer.signal("move arms")
  relayer.signal("talking")

  response = get_response(phrase) # picks one of several appropriate responses (video title) based on keyword 
                                  # based if keyword is contained on the given phrase 
  responder.express(response)     # plays the corresponding video given the title of the video 

##################################################################################

responder.default()      #shows default eye image on screen

while True:

  if (pir.motion_detected())
    relayer.signal("life detected")
    responder.greet()

  relayer.signal("listening")
  phrase = listener.hear()
  relayer.signal("message decoded")

  if not phrase: continue
  
  key = directive.command(phrase)
  
  if key:
    obey_mode(key)
  else: 
    reply(phrase)

##################################################################################

class Directive:
  def __init__(trigger):
    self.trigger = trigger

  def check(self, phrase):
    return self.trigger in phrase

  def command(phrase):
    all_words = phrase.split()
    command_index = all_words.index(pass_phrase) + 1
    command = all_words[command_index]
    return command