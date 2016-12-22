from responder import Responder
from time import sleep

responder = Responder()
responder.default()

while True:
  sleep(3)
  Responder.express("Hellobot_Help""1")
  sleep(3)
  Responder.express("Hellobot_Help", "2")
  sleep(3)
