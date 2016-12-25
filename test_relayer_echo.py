from relayer import Relayer 
from time import sleep

relayer = Relayer()

relayer.print_keys()

print "connected?", relayer.check_connection()

print ("connecting...")
relayer.connect()

print "connected?", relayer.check_connection()

#signal and command are the same in routine, 
#command means you are ordering something, signal means you are just informing
relayer.signal("listening")
sleep(3)

relayer.signal("message decoded")
sleep(3)

relayer.command("move arms")
sleep(3)

relayer.command("forward")
sleep(3)

relayer.command("left")
sleep(3)

relayer.command("right")
sleep(3)
