from listener import Listener

listener = Listener()

while True:
  print "say something!"
  key = listener.hear()

  if key:
    print key