from listener import Listener
from eye import Eye
import random

listener = Listener()
eye = Eye()

def get_response_keys(phrase):  

  if "hello" in phrase or "hey" in phrase or "hi" in phrase: #greet
  elif "how are you" in phrase: #how are you?
  elif "up" in phrase or "whatsApp" in phrase: #what's up?
  elif "name" in phrase: #what's your name?
  elif "do you do" in phrase: #what do you do?
  elif "office" in phrase: #is anyone in the office?
  elif "plans" in phrase or "tonight" in phrase: #what are your plans tonight?
  elif "bathroom" in phrase: #where is the bathroom?
  elif "advice" in phrase: #do you have advice?
  elif "idea" in phrase or "help" in phrase: #i need an idea
  else:
    
 

eye.default()

while True:
  
  phase = listener.hear()
  
  if phrase:
  	k, i = get_response_keys(phrase)
    eye.express(k, i)