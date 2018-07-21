from picamera import PiCamera
import picamera.array
import cv2 
import numpy 
import os
from time import sleep

CASCADE_PATH = '/home/pi/hellobot/cascade/haarcascade_frontalface_default.xml'
SHOW_FACE_IMAGE = "sudo fbi -T 1 -d /dev/fb0 -a -noverbose /home/pi/hellobot/images/current2.jpg &"
CURRENT_IMAGE_PATH = "/home/pi/hellobot/images/current.jpg"
CURRENT_MARKED_IMAGE_PATH = "/home/pi/hellobot/images/current2.jpg"
SHOW_IMAGE = "sudo fbi -T 1 -d /dev/fb0 -a -noverbose /home/pi/hellobot/images/current.jpg &"
REMOVE_IMAGE = "sudo killall -3 fbi"

class FaceFinder:

  def __init__(self):
    self.camera = PiCamera()
    self.camera.resolution = (320, 240)
    self.cascade = cv2.CascadeClassifier(CASCADE_PATH)
    self.image = None
    self.has_faces = False
    self.has_faces_previous = False
    self.faces = None
    self.camera.start_preview()
    sleep(3)

  def run(self, box = True):

    self.has_faces_previous = self.has_faces

    self.camera.capture(CURRENT_IMAGE_PATH)                     #get picture
    self.image = cv2.imread(CURRENT_IMAGE_PATH, 1)              #convert this to opencv image
    gray = cv2.cvtColor(self.image, cv2.COLOR_BGR2GRAY)         #convert this to grey    
    self.faces = self.cascade.detectMultiScale(image = gray, scaleFactor = 1.4, minNeighbors = 6, minSize = (30, 30), maxSize = (240, 240))
    # see http://stackoverflow.com/questions/20801015/recommended-values-for-opencv-detectmultiscale-parameters

    if len(self.faces):
      self.has_faces = True
      if box == True: self.box_faces()   
    else:
      self.has_faces = False
      
  def show(self, update = True):

    if update: self.run()

    if self.has_faces and self.has_faces_previous:
      os.system(REMOVE_IMAGE)
      os.system(SHOW_FACE_IMAGE)
    elif self.has_faces:
      self.camera.stop_preview() 
      os.system(SHOW_FACE_IMAGE) 
    elif self.has_faces_previous: 
      os.system(REMOVE_IMAGE)
      self.camera.start_preview()
 
  def box_faces(self):
    #print "found: " + str(len(self.faces)) + " face(s)"
    #put rectangle on each face and save picture    
    for (x, y, w, h) in self.faces:
      cv2.rectangle(self.image, (x, y),(x + w, y + h), (255, 255, 0), 2)
     
    cv2.imwrite(CURRENT_MARKED_IMAGE_PATH, self.image)
    
  def face_detected(self, update = True):

    if update: self.run()
    return self.has_faces

  def shutdown(self):
    if self.has_faces:
      os.system(REMOVE_IMAGE)
    else:
      self.camera.stop_preview()
    self.camera.close()
