import speech_recognition as sr
import random 

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
      print "GIBBERISH"
    except sr.RequestError as e:
      print("REQUEST ERROR: {0}".format(e))

    return phrase