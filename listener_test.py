from listener import Listener
import os

listener = Listener()

#--adev alsa
PATH = "/home/pi/hellobot/videos/"
START_COMMAND = "omxplayer -o local --win 0,0,480,800 /home/pi/hellobot/videos/"

while True:

  os.system("sudo fbi --noverbose -T 2 ./videos/cat.jpg &")
    
  key = listener.hear()

  if key:
    print key

    if "hello" in key or "hi" in key or "hey" in key:
      os.system(START_COMMAND + "hello.mp4")
    elif "goodbye" in key:
      os.system(START_COMMAND + "whatsup.mp4")
    elif "help" in key:
      os.system(START_COMMAND + "help.mp4")
    elif "black" in key:
      os.system("xset dpms force off") #turn off black light
    elif "shutdown" in key:
      os.system("sudo shutdown -h now")
    



  
