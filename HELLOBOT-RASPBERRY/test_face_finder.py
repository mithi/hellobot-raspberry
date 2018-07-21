from face_finder import FaceFinder
import os 

FACE = "sudo fbi -T 1 -d /dev/fb0 -a -noverbose /home/pi/hellobot/images/default-eye.jpg"

face_finder = FaceFinder()

for _ in range(100):
  face_finder.show()

face_finder.shutdown()
os.system(FACE)
