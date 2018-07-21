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
raw_input("press any key to continue")

relayer.signal("message decoded")
raw_input("press any key to continue")

relayer.command("move arms")
raw_input("press any key to continue")

relayer.command("back")
raw_input("press any key to continue")

relayer.command("forward")
raw_input("press any key to continue")

relayer.command("left")
raw_input("press any key to continue")

relayer.command("right")
raw_input("press any key to continue")

