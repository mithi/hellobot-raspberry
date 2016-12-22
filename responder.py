import os

DEFAULT_STATIC_PATH = "/home/pi/hellobot/images/default-eye.jpg"
ANIMATION_PATH = "/home/pi/hellobot/videos/"
START_ANIMATION_COMMAND = "omxplayer -o alsa --win 0,0,480,800 "
DEFAULT_FRAME_COMMAND = "fbi -T 1 -d /dev/fb0 -a -noverbose /home/pi/hellobot/images/default-eye.jpg &"
REMOVE_EYE_COMMAND = "killall -3 fbi"
LOW_POWER_COMMAND = "xset dpms force off"

class Responder:
  def __init__(self):
    self.static_eye = DEFAULT_FRAME_COMMAND
    self.animate_key = START_ANIMATION_COMMAND + ANIMATION_PATH
    self.low_power = LOW_POWER_COMMAND
    self.remove_key = REMOVE_EYE_COMMAND

  def express(self, key):
  	os.system(self.animate_key + key + ".mp4")

  def default(self):
        print self.static_eye
  	os.system(self.static_eye)

  def black(self):
  	os.system(self.low_power)
  
  def remove(self):
  	os.system(self.remove_key)
