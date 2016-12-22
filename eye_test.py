from eye import Eye
from time import sleep

eye = eye()

while True:
	eye.default()
	sleep(3)
	eye.express("Hellobot_Help", "001")
	sleep(3)
	eye.express("Hellobot_Help", "002")
	sleep(3)
