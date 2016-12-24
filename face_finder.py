from picamera import PiCamera
import picamera.array
import cv2 
import numpy 
import os

CASCADE_PATH = '/home/pi/hellobot/cascade/haarcascade_frontalface_default.xml'
SHOW_IMAGE = "sudo fbi -T 1 -d /dev/fb0 -a -noverbose /home/pi/hellobot/images/current2.jpg &"
CURRENT_IMAGE_PATH = "/home/pi/hellobot/images/current.jpg"
CURRENT_IMAGE_PATH_WITH_RECTANGLE = "/home/pi/hellobot/images/current2.jpg"


class FaceFinder:

  def __init__(self):
    self.camera = PiCamera()
    self.camera.resolution = (320, 240)
    self.cascade = cv2.CascadeClassifier(CASCADE_PATH) 

  def run(self):

    #get picture
    self.camera.capture(CURRENT_IMAGE_PATH, format='jpeg')

    #convert this to opencv image
    image = cv2.imread(CURRENT_IMAGE_PATH, 1)

    #convert this to grey
    gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    
    #look for face
    faces = self.cascade.detectMultiScale(gray, 1.1, 5)

    if len(faces) > 0:

      print "found: " + str(len(faces)) + " face(s)"
    
      #put rectable on face
      for (x, y, w, h) in faces:
        cv2.rectangle(image, (x, y),(x + w, y + h),(255,255,0), 2)
     
      #show picture
      cv2.imwrite(CURRENT_IMAGE_PATH_WITH_RECTANGLE, image)
      os.system(SHOW_IMAGE)
      
    else:
      print "no face detected"


