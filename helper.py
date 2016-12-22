import random

def get_response_key(phrase):  

  if "hello" in phrase or "hey" in phrase or "hi" in phrase: #greet
    key = "hello" + str(random.randint(1, 6))
  elif "how are you" in phrase: #how are you?
    key = "how" + str(random.randint(1,5))
  elif "up" in phrase or "whatsApp" in phrase: #what's up?
    key = "up" + str(random.randint(1, 4))
  elif "name" in phrase: #what's your name?
    key = "name" + str(random.randint(1, 4))
  elif "do you do" in phrase: #what do you do?
    key = "do" + str(random.randint(1, 4))
  elif "office" in phrase: #is anyone in the office?
    key = "" + str(random.randint())
  elif "plans" in phrase or "tonight" in phrase: #what are your plans tonight?
    key = "plans" + str(random.randint(1, 5))
  elif "bathroom" in phrase: #where is the bathroom?
    key = "bathroom" + str(random.randint(1, 3))
  elif "advice" in phrase: #do you have advice?
    key = "advice" + str(random.randint(1, 7))
  elif "idea" in phrase or "help" in phrase: #i need an idea
    key = "help" + str(random.randint(1,11))
  else:
  	key = "catch" + str(random.randint(1, 2))

  return key