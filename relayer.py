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
      "left": 'R',
      "right": 'L',
      "backward": 'B',
      "smart forward": 'S'
    }
  
  def connect(self):
    
    success = self.connect_port(self.ser1)
    
    if not success:
      self.connect_port(self.ser2)

  def signal(self, message):
    self.write(message)

  def command(self, message):
    # signal and command are the same in routine, command means you're ordering something, signal you are just informing
    self.write(message)

  def connect_port(self, ser):
    
    success = False
    
    try:
      self.port = serial.Serial(port = ser, baudrate = self.baudrate, timeout = 3.0)
      success = True
      self.is_connected = True
      print "Connected to:", ser
    except:
      self.is_connected = False 
      print "Error connecting to port:", ser

    return success

  def key(self, message):
    
    key = None

    try:
      key = self.keys[message]
    except KeyError:
      print "No such key"
    
    print "Message | Key :", message, "|", key
    return key 

  def write(self, message):
  
    key = self.key(message)
    
    if self.port:
      if key:
        self.port.write(key) 
        print "SENT: Key | Message:", key, "|", message
      else:
        print "No key sent"
    else:
      print "No port, try running connect() or check your connection"

  def print_keys(self):
    for k, v in self.keys.items():
      print k, v

  def check_connection(self):
    return self.is_connected    

