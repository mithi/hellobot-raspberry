from relayer import Relayer
from robot_modules import Listener, Responder, get_response
from time import sleep 

relayer = Relayer()
response = Responder()

print "connected?", relayer.check_connection()

print ("connecting...")
relayer.connect()

print "connected?", relayer.check_connection()

response.default()

while True:
  
  x = raw_input("s f b l r a 1 2 3 4 e:")

  if x == 's':
    response.sleep()
    relayer.signal("listening")
    sleep(0.25)
    relayer.signal("message decoded")
    sleep(2)
    response.wake()
    response.default()
    #relayer.command("move arms")
    relayer.command("forward")
    relayer.command("back")
    #relayer.command("left")
    #relayer.command("right")
    #relayer.command("move arms")
    sleep(3)
    response.show("EVERYONE")
    #relayer.command("move arms")
  
  elif x == 'f':
    relayer.command("forward")

  elif x == 'b':
    relayer.command("back")

  elif x == 'l':
    relayer.command("left")

  elif x == 'r':
    relayer.command("right")

  elif x == 'a':
    relayer.command("move arms")

  elif x == '1':
    response.show("hello1")

  elif x == '2':
    response.show("hello4")

  elif x == '3':
    response.show("up4")

  elif x == '4':
    response.show("do1")

  elif x == 'e':
    break
