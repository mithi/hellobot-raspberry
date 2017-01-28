import speech_recognition as sr
import random 
import os

DEFAULT_STATIC_PATH = "/home/pi/hellobot/images/default-eye.jpg"
ANIMATION_PATH = "/home/pi/hellobot/videos/"
START_ANIMATION_COMMAND = "omxplayer -o local --win 0,0,480,800 " # -o alsa
DEFAULT_FRAME_COMMAND = "sudo fbi -T 1 -d /dev/fb0 -a -noverbose /home/pi/hellobot/images/default-eye.jpg &" #remove sudo if unnecessary
REMOVE_EYE_COMMAND = "killall -3 fbi"
LOW_POWER_COMMAND = "xset dpms force off"

class Responder:
  def __init__(self):
    self.static_eye = DEFAULT_FRAME_COMMAND
    self.animate_key = START_ANIMATION_COMMAND + ANIMATION_PATH
    self.low_power = LOW_POWER_COMMAND
    self.remove_key = REMOVE_EYE_COMMAND

  def express(self, key):
    os.system(self.animate_key + key + ".mp4")

  def default(self):
        print self.static_eye
    os.system(self.static_eye)

  def black(self):
    os.system(self.low_power)
  
  def remove(self):
    os.system(self.remove_key)

class Listener:
  
  def __init__(self):
    self.r = sr.Recognizer()

  def hear(self):
    return self.recognize(self.obtain_audio())
  
  def obtain_audio(self):
    with sr.Microphone(device_index = 0, sample_rate = 48000, chunk_size = 1024) as source:
      return self.r.listen(source)
  
  def recognize(self, audio):
    phrase = None

    try:
      phrase = self.r.recognize_google(audio)
    except sr.UnknownValueError:
      pass
      #print "GIBBERISH"
    except sr.RequestError as e:
      pass
      #print("REQUEST ERROR: {0}".format(e))

    return phrase
