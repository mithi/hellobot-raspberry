from robot_modules import Directive, Responder, Listener
from time import sleep 

def directive_test():
  
  TRIGGER_WORD = "super"
  directive = Directive(TRIGGER_WORD)  
  
  # command in the middle
  x = directive.command("happy birthday super hero yes yes yes")
  a = "OK" if x == "hero" else "FAIL"
  print a 

  # command at the start
  x = directive.command("super dance happy birthday super hero yes yes yes")
  a = "OK" if x == "dance" else "FAIL"
  print a 
  
  #two commands, only execute first command
  x = directive.command("hey super dancer happy birthday super hero yes yes yes")
  a = "OK" if x == "dancer" else "FAIL"
  print a 

  # trigger word repeated consecutively before command will not be detected
  x = directive.command("happy birthday super super super nonsense hahaha")
  a = "OK" if x == "super" else "FAIL"
  print a 

  # command at the end 
  x = directive.command("happy birthday super world")
  a ="OK" if x == "world" else "FAIL"
  print a 



def responder_test():
  responder = Responder()

  print "low power mode for three seconds"
  sleep(2)

  responder.sleep()
  sleep(10)

  responder.wake()
  sleep(10)

  responder.default()

  print "loop all videos"
  
  responder.greet()
  
  responder.show("advice1")
  responder.show("advice2")
  responder.show("advice3")
  responder.show("advice4")
  responder.show("advice5")
  responder.show("advice6")
  responder.show("advice7")
  responder.show("bathroom1")
  responder.show("bathroom2")
  responder.show("bathroom3")
  responder.show("catch1")
  responder.show("catch2")
  responder.show("do1")
  responder.show("do2")
  responder.show("do3")
  responder.show("do4")
  responder.show("hello1")
  responder.show("hello2")
  responder.show("hello3")
  responder.show("hello4")
  responder.show("hello5")
  responder.show("hello6")
  responder.show("help1")
  responder.show("help2")
  responder.show("help3")
  responder.show("help4")
  responder.show("help5")
  responder.show("help6")
  responder.show("help7")
  responder.show("help8")
  responder.show("help9")
  responder.show("help10")
  responder.show("help11")
  responder.show("how1")
  responder.show("how2")
  responder.show("how3")
  responder.show("how4")
  responder.show("how5")
  responder.show("name1")
  responder.show("name2")
  responder.show("name3")
  responder.show("name4")
  responder.show("office1")
  responder.show("plans1")
  responder.show("plans2")
  responder.show("plans3")
  responder.show("plans4")
  responder.show("plans5")
  responder.show("up1")
  responder.show("up2")
  responder.show("up3")
  responder.show("up4")

  responder.default()
  sleep(10)
  responder.remove()

  print "test complete"

def listener_test():

  listener = Listener()
  
  while True:
    x = raw_input("press k to say something! press e to exit!")
    if x == 'k':
      print "say something..."
      phrase = listener.hear()
      print "you said:", phrase
    if x == 'e':
      break

print "directive test result:"
directive_test()

print "listener test result:"
listener_test()

print "responder test result:"
responder_test()
