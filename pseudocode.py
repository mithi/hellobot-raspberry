import speech_recognition as sr
import random 

class Listener:
  
  def __init__(self):
    self.r = sr.Recognizer()

  def hear(self):
    return self.recognize(self.obtain_audio())
  
  def obtain_audio(self):
    with sr.Microphone() as source:
      return self.r.listen(source)
  
  def recognize(self, audio):
    phrase = None

    try:
      phrase = self.r.recognize_google(audio)
    except sr.UnknownValueError:
      print "GIBBERISH"
    except sr.RequestError as e:
      print("REQUEST ERROR: {0}".format(e))

    return phrase

VIDEO_PATH = "/home/pi/robo/videos/"
listener = Listener()

def map_to_path(phrase):  

  if "hello" in phrase or "hey" in phrase or "hi" in phrase: #greet
    path = "hi00" + str(random.randint(1, 5))
  elif "how are you" in phrase: #how are you?
    path = ""
  elif "up" in phrase: #what's up?
    path = ""
  elif "name" in phrase: #what's your name?
    path = ""
  elif "do you do" in phrase: #what do you do?
    path = ""
  elif "office" in phrase: #is anyone in the office?
    path = ""
  elif "plans" in phrase or "tonight" in phrase: #what are your plans tonight?
    path = "" 
  elif "bathroom" in phrase: #where is the bathroom?
    path = ""
  elif "advice" in phrase: #do you have advice?
    path = ""
  elif "idea" in phrase or "help" in phrase: #i need an idea
    path = ""
  else:
    path = "" #catch all phrase
  
  path = VIDEO_PATH + path + ".mp4"

  return path

def move(key):

  # FORWARD, LEFT, OR RIGHT
  # if and until nothing is in the way according to camera and obstacle sensors,
  # otherwise display video "hindi ako tanga"
  # if it sees a face, it will greet the person.

  if "forward" in key:
    forward_routine()
  elif "left" in key:
    left_routine()
  elif "right" in key:
    right_routine()

def talk(key):
  display(map_to_path(key))

#########################################################################

while True:

  if PIR.detect(): greet()  
    
  key = listener.hear()        
  
  if key:
    display(loading_path)
    move(key) 
    talk(key)