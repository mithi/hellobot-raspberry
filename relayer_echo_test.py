from relayer import Relayer 

relayer = Relayer()

print ("keys:"), relayer.keys()

print "connected?", relayer.is_connected()

print ("connecting...")
relayer.connect()

print "connected?", relayer.is_connected()

#signal and command are the same in routine, 
#command means you are ordering something, signal means you are just informing
relayer.signal("listening")
relayer.signal("message decoded")
relayer.command("forward")
relayer.command("left")
relayer.command("right")

#prints out actual response from arduino
print relayer.raw_answer("obstacle?")

#answers are only true or false
print relayer.answer("obstacle")