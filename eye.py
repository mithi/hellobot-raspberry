import os

DEFAULT_STATIC_PATH = "home/pi/hellobot/images/default-eye.jpg"
ANIMATION_PATH = "/home/pi/hellobot/videos/"
START_ANIMATION_COMMAND = "omxplayer -o alsa --win 0,0,480,800 "
DEFAULT_FRAME_COMMAND = "sudo fbi -T 1 -d /dev/fb0 -a -noverbose "
REMOVE_EYE_COMMAND = "sudo killall -3 fbi"
LOW_POWER_COMMAND = "xset dpms force off"

class Eye:
  def __init__(self):
    self.static_eye = DEFAULT_FRAME_COMMAND + DEFAULT_STATIC_PATH 
    self.animate_key = START_ANIMATION_COMMAND + ANIMATION_PATH
    self.low_power = LOW_POWER_COMMAND
    self.remove_key = REMOVE_EYE_COMMAND

  def express(self, key, id):
  	os.system(self.animate_key + key + id + ".mp4")

  def default(self):
  	os.system(self.static_eye)

  def black(self):
  	os.system(self.low_power)
  
  def remove(self):
  	os.system(self.remove_key)