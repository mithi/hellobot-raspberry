from listener import Listener
from responder import Responder
from helper import get_response

listener = Listener()
responder = Responder()

responder.default()

while True:
  
  phrase = listener.hear()
  
  if phrase:
    response = get_response(phrase)
    responder.express(response)
