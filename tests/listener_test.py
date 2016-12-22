from listener import Listener
import os
from time import sleep

listener = Listener()

#--adev alsa
PATH = "/home/pi/hellobot/videos/"
START_COMMAND = "omxplayer -o local --win 0,0,480,800 /home/pi/hellobot/videos/"

os.system("sudo fbi -T 1 -d /dev/fb0 -a -noverbose -t 1 ./videos/cat.jpg &")

while True:
    
  key = listener.hear()

  if key:
    print key

    if "hello" in key or "hi" in key or "hey" in key:
      print "hello"
      #os.system(START_COMMAND + "hello.mp4")
    elif "goodbye" in key:
      print "goodbye"
      #os.system(START_COMMAND + "whatsup.mp4")
    elif "help" in key:
      print "help"
      #os.system(START_COMMAND + "help.mp4")
    elif "black" in key:
      os.system("sudo killall -3 fbi")
      os.system("xset dpms force off") #turn off black light
      sleep(5)
      os.system("sudo fbi -T 1 -d /dev/fb0 -a -noverbose -t 1 ./videos/cat.jpg &")
    elif "shutdown" in key:
      os.system("sudo shutdown -h now")
    elif "break" in key:
      break
    



  
