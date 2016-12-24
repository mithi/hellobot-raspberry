from picamera import PiCamera
import picamera.array
import cv2 
import numpy 
import io 

CASCADE_PATH = '/home/pi/hellobot/cascade/haarcascade_frontalface_default.xml'

class FaceFinder:

  def __init__(self):
    self.stream = io.BytesIO()
    self.camera = PiCamera()
    self.camera.resolution = (320, 240)
    self.camera.framerate = 24
    self.cascade = cv2.CascadeClassifier(CASCADE_PATH) 
    self.buff = None
    self.image = None
    self.gray = None
    self.faces = None

  def run(self):

    #get picture
    self.camera.capture(self.stream, format='jpeg')
    
    #convert picture to array 
    self.buff = numpy.fromstring(self.stream.getvalue(), dtype=numpy.uint8)
    
    #convert this to opencv image
    self.image = cv2.imdecode(self.buff, 1)

    #convert this to grey
    self.gray = cv2.cvtColor(self.image, cv2)
    
    #look for face
    self.faces = face_cascade.detectMultiScale(self.gray, 1.1, 5)

    print "found: " + str(len(self.faces)) + " face(s)"
    
    #put rectable on face
    for (x, y, w, h) in self.faces:
      cv2.rectangle(self.image,(x, y),(x + w, y + h),(255,255,0),2)
    
    #show picture
    cv2.imshow(self.image)

  def save(self):

    cv2.imwrite("current.jpg", self.image)



