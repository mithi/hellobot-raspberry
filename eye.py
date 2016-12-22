import os

DEFAULT_STATIC_PATH = "home/pi/hellobot/images/default-eye.jpg"
ANIMATION_PATH = "/home/pi/hellobot/videos"
START_ANIMATION_COMMAND = "omxplayer -o alsa --win 0,0,480,800"
DEFAULT_FRAME_COMMAND = "sudo fbi -T 1 -d /dev/fb0 -a -noverbose"
KILL_DEFAULT_FRAME_COMMAND = ""
class Eye:
  def __init__(self):
    self.static_eye = DEFAULT_STATIC_PATH; 

  def express(key, id):