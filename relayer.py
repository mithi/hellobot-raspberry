import serial

class Relayer:

  def __init__(self, baudrate = 9600):
    self.ser1 = "/dev/ttyACM0"
    self.ser2 =  "/dev/ttyACM1"
    self.baudrate = baudrate
    self.port = None 
    self.is_connected = False
    self.keys = {
      "listening": 'H', 
      "message decoded": 'D',
      "move arms": 'A',
      "forward": 'F',
      "left": 'L',
      "right": 'R',
      "reverse": 'B'
    }
  
  def connect(self):
    
    success = self.connect_port(self.ser1)
    
    if not success:
      self.connect_port(self.ser2)

  def signal(self, message):
    self.write(message)

  def command(self, message):
    #signal and command are the same in routine, 
    #command means your ordering something, signal you are just informing
    self.write(message)

  def connect_port(self, ser):
    
    success = False
    
    try:
      self.port = serial.Serial(port = ser, baudrate = self.baudrate, timeout = 3.0)
      success = True
      self.is_connected = True
      print "connected to:", ser
    except:
      self.is_connected = False 
      print "error connecting to port:", ser

    return success

  def key(self, message):

    print "message is:", message
    
    key = None

    try:
      key = self.keys[message]
      print "key is:", key
    except KeyError:
      print "No such key"

    return key 

  def write(self, message):
  
    key = self.key(message)
    
    if self.port:
      if key:
        self.port.write(key) 
        print "finished sending key:", key
      else:
        print "no key sent"
    else:
      print "no port, try running connect() or check your connection"

  def print_keys(self):
    for k, v in self.keys.items():
      print k, v

  def check_connection(self):
    return self.is_connected    

