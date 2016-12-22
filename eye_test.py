from responder import Responder
from time import sleep

responder = Responder()
responder.default()

while True:
  sleep(3)
  Responder.express("hello1")
  sleep(3)
  Responder.express("hello2")
  sleep(3)
