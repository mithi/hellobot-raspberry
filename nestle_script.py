import RPi.GPIO as GPIO
from robot_modules import Listener, Responder, Directive
from face_finder import FaceFinder
from relayer import Relayer
from time import sleep 
from random import randint
import os
import sys

############################################################

TRIGGER_WORD = "robot"
directive = Directive(TRIGGER_WORD)

NESTLE_VIDEOS = "/home/pi/hellobot/mped_videos/"         
responder = Responder(path = NESTLE_VIDEOS)         # plays video on screen 

PIR_PIN = 26
GPIO.setmode(GPIO.BCM)
GPIO.setup(PIR_PIN, GPIO.IN)

listener = Listener()                               # listens to microphone and outputs text
relayer = Relayer()                                 # communicates to arduino

############################################################

def get_nestle_response(phrase):  
  
  if "hello" in phrase or "hey" in phrase or "hi" in phrase: #greet
    key = "hello" + str(randint(1, 3))
  elif "how" in phrase: #how are you?
    key = "how" + str(randint(1, 3))
  elif "up" in phrase or "whatsApp" in phrase: #what's up?
    key = "up" + str(randint(1, 3))
  elif "name" in phrase: #what's your name?
    key = "else"
  elif "do" in phrase: #what do you do?
    key = "do" + str(randint(1, 3))
  elif "plans" in phrase or "tonight" in phrase: #what are your plans tonight?
    key = "plans" + str(randint(1, 2))
  elif "advice" in phrase or "help" in phrase: #do you have advice?
    key = "advice" + str(randint(1, 2))
  elif "idea" in phrase : #i need an idea
    key = "idea" + str(randint(1, 2))
  else:
    key = "else"

  return key

############################################################

def stop_camera():
  try:
    os.system("/home/pi/RPi_Cam_Web_Interface/stop.sh")
  except:
    pass

def smart_camera():
  COUNT = 15
  face_finder = FaceFinder()
  for _ in range(COUNT):
    face_finder.show()
  face_finder.shutdown()
  responder.default()
  
def obey(key):
  if key in ['forward', 'back', 'left', 'right']: relayer.command(key)
  if key == 'die': os.system("sudo shutdown -h now")
  if key == 'camera': smart_camera()
  if key == "sing" or key == "saying": responder.show("sing" + str(randint(1, 2)))

def listen():
  #responder.show("listening-transition-A")
  responder.remove()
  responder.listening()
  phrase = listener.hear()
  print phrase
  #responder.show("listening-transition-B")
  responder.remove()
  responder.default()
  return phrase

def reply(key):
  relayer.command("move arms")
  print "reply - key:", key
  responder.show(key)

def interact():
  phrase = listen()
  if phrase:
    key = directive.command(phrase)
    obey(key) if key else reply(get_nestle_response(phrase))

def greet():
  relayer.signal("move arms")
  responder.remove()
  responder.default()
  responder.wake()
  responder.show("greet" + str(randint(1,2)))


############################################################

def cleanup():
  print "quitting..."
  GPIO.cleanup()
  responder.sleep()
  stop_camera()
  sys.exit()
      
def main():
  
  if GPIO.input(PIR_PIN): #person detected for the first time
    greet()

    for x in range(20):
      interact()

  responder.sleep()
  print "no person detected"
  sleep(0.5)

if __name__ == '__main__':
  
  responder.default()               #shows default eye image on screen
  relayer.connect()                 #connect to arduino port
  stop_camera()
  
  while True:
    try:
      main()
    except KeyboardInterrupt:
      cleanup()

############################################################
