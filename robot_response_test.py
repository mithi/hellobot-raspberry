from listener import Listener
from responder import Responder
from helper import get_response_keys

listener = Listener()
responder = Responder()

responder.default()

while True:
  
  phase = listener.hear()
  
  if phrase:
  	key = get_response_keys(phrase)
    responder.express(key)