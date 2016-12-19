from responder import Responder
from time import sleep

responder = Responder()
responder.default()

while True:
  sleep(3)
  responder.express("hello1")
  sleep(3)
  responder.express("hello2")
  sleep(3)
