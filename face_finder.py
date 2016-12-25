from picamera import PiCamera
import picamera.array
import cv2 
import numpy 
import os

CASCADE_PATH = '/home/pi/hellobot/cascade/haarcascade_frontalface_default.xml'
SHOW_IMAGE2 = "sudo fbi -T 1 -d /dev/fb0 -a -noverbose /home/pi/hellobot/images/current2.jpg &"
CURRENT_IMAGE_PATH = "/home/pi/hellobot/images/current.jpg"
CURRENT_MARKED_IMAGE_PATH = "/home/pi/hellobot/images/current2.jpg"
SHOW_IMAGE = "sudo fbi -T 1 -d /dev/fb0 -a -noverbose /home/pi/hellobot/images/current.jpg &"

class FaceFinder:

  def __init__(self):
    self.camera = PiCamera()
    self.camera.resolution = (320, 240)
    self.cascade = cv2.CascadeClassifier(CASCADE_PATH)
    self.image = None
    self.has_faces = False
    self.faces = None

  def run(self, box = True):

    self.camera.capture(CURRENT_IMAGE_PATH, format='jpeg')      #get picture
    self.image = cv2.imread(CURRENT_IMAGE_PATH, 1)              #convert this to opencv image
    gray = cv2.cvtColor(self.image, cv2.COLOR_BGR2GRAY)         #convert this to grey    
    self.faces = self.cascade.detectMultiScale(gray, 1.1, 5)    #look for face -- FIXME: tweak middle variable for performance

    if len(self.faces):
      self.has_faces = True
      if box = True: self.box_faces()   
    else:
      self.has_faces = False
      
  def show(self, update = True):

    if update: self.run()

    if self.has_faces:
      os.system(SHOW_IMAGE2)
    else:
      os.system(SHOW_IMAGE)
 
  def box_faces(self):
    
    for (x, y, w, h) in self.faces:
      cv2.rectangle(self.image, (x, y),(x + w, y + h), (255, 255, 0), 2) #put rectangle on each face
     
    cv2.imwrite(MARKED_IMAGE_PATH, self.image) #save picture
    print "found: " + str(len(faces)) + " face(s)"

  def face_detected(self, update = True):

    if update: self.run()
    return self.has_faces


