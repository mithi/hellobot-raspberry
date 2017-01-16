from relayer import Relayer
from robot_modules import Listener, Responder, get_response

relayer = Relayer()
response = Responder()

relayer.print_keys()

print "connected?", relayer.check_connection()

print ("connecting...")
relayer.connect()

print "connected?", relayer.check_connection()


while True:

  x = raw_input("F B L R A H D S X 1 - 8:")
  
  if x == '1':
    response.show("hello5") 
    #how may i help you!

  if x == '2':
    response.show("do4") 
    #I aspire to help humanity but I was programmed to say hello to you

  if x == '3':
    response.show("do1") 
    #Prove entertainment and demonstrate Dentsu creativity to people such as yourself, are you impressed?

  if x == '4':
    response.show("how1")
    #I'm good, wish I had feelings though

  if x == '5':
    response.show("advice4")
    #I wish I knew how you were feeling cuz I'm a robot with no feelings

  if x == '6':
    response.show("help11")
    #I wasn't programmed to solve your creative problems, If I were, you wouldn't have a job
  
  if x == '7':
    response.show("advice5")
    #follow your heart bes

  if x == '8':
    response.show("up4")
    #I wasn't programmed to respond to existential inquiries

  if x == 'G':
    relayer.command("move arms")
    response.show("hello3")

    response.show("g_Alex")
    response.show("g_Bea")
    response.show("g_Carlo01")
    response.show("g_Ed")
    response.show("g_Era")
    response.show("g_Eric")
    response.show("g_Kathy")
    response.show("g_RenRen")
    response.show("g_MVP")

    relayer.command("move arms")
    response.show("hello4")

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
