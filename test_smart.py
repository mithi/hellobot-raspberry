from relayer import Relayer
from robot_modules import Listener, Responder, get_response

relayer = Relayer()
responder = Responder()

relayer.print_keys()

print "connected?", relayer.check_connection()

print ("connecting...")
relayer.connect()

print "connected?", relayer.check_connection()

while True:

  x = raw_input("F B L R A H D S X G:")
  
  if x == 'G':
    response.show("g_Alex")
    response.show("g_Bea")
    response.show("g_Carlo01")
    response.show("g_Carlo02")
    response.show("g_Ed")
    response.show("g_Eric")
    response.show("g_Kathy")
    response.show("g_RenRen")

  if x == 'F':
    relayer.command("forward")

  if x == 'B':
    relayer.command("backward")

  if x == 'L':
    relayer.command("left")

  if x == 'R':
    relayer.command("right")

  if x == 'A':
    relayer.command("move arms")

  if x == 'H':
    relayer.signal("listening")

  if x == 'D':
    relayer.signal("message decoded")

  if x == 'S':
    relayer.command("smart forward")

  if x == 'X':
    break
