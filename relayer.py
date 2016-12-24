import Serial

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
      "obstacle?": 'O',
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

  def answer(self, question):
    #answers are only true or false

    answer = False

    raw_answer = self.raw_answer(question)

    if raw_answer == "T":
      answer = True

    return answer 
  
  def raw_answer(self, question):

    #actual response from arduino 
    
    answer = None 
    COUNT = 1000000
    
    self.write(question)

    for _ in range(COUNT):

      if self.port.in_waiting:
        answer = self.port.readline()
        print answer
        break
    
    if not answer: print "timed out: no answer given"

    return answer


  def connect_port(self, ser):
    
    success = False
    
    try:
      self.port = serial.Serial(port = ser, baudrate = self.baudrate)
      success = True
      self.is_connected = True
      print "connection successful!"
    except:
      self.is_connected = False 
      print "error connecting to port:", ser

    return success

  def key(self, message):

    print "message is:", message
    
    key = None

    try:
      key = self.keys.message[message]
    except KeyError:
      print "No such key"

    return key 

  def write(self, message):

    key = self.key("message")

    if key:
      self.port.write(key) 

  def keys(self):
    return self.keys

  def is_connected(self):
    return self.is_connected    

