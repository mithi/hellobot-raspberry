
from hexy.robot.core import *
import time
import Adafruit_ADS1x15

# https://github.com/adafruit/Adafruit_Python_ADS1x15/
# https://github.com/mithi/hexy/
# https://github.com/slaattnes/hexy

GAIN = 16 # +/-0.256V, 0.125 V resolution
adc = Adafruit_ADS1x15.ADS1115() # Address: 0x48

hexy = HexapodCore() # Address: 0x40, 0x41 
tripod1 = [hexy.right_front, hexy.left_middle, hexy.right_back]
tripod2 = [hexy.left_front, hexy.right_middle, hexy.left_back]

# -- 
# HELPER FUNCTIONS
# --

def sleep_hack():
  # NOTE: Hexy needs to rest every now and then to prevent servo overloading
  
  time.sleep(0.25) # TODO: Calibrate this, time it takes to perform the movement
  hexy.off()
  time.sleep(0.25) # TODO: Calibrate this, time to rest 

# --
# BASIC LEG FUNCTIONS
# --
  
def bend(leg, new_hip_angle):
  leg.pose(hip_angle = new_hip_angle, knee_angle = 90, ankle_angle = 70)
  
def neutral(leg, new_hip_angle):
  leg.pose(hip_angle = new_hip_angle, knee_angle = 0, ankle_angle = 0)
  
def stretch(leg, new_hip_angle):
  leg.pose(hip_angle = new_hip_angle, knee_angle = -70, ankle_angle = -30)

# --
# BASIC HEXAPOD FUNCTIONS
# --

def do_neutral_stance():
    
  # Raise tripod1
  for leg in tripod1:
    bend(leg, new_hip_angle = 0)
  
  sleep_hack()
  
  # Put tripod1 down
  for leg in tripod1:
    neutral(leg, new_hip_angle = 0)

  sleep_hack()

  # Raise tripod2
  for leg in tripod2:
    bend(leg, new_hip_angle = 0)
  
  sleep_hack()
  
  # Put tripod2 down
  for leg in tripod2:
    neutral(leg, new_hip_angle = 0)

  sleep_hack()


def do_walk_stance(offset = 35):
  
  # Raise tripod1 with appropriate hip angles
  bend(hexy.right_front, new_hip_angle = -offset)
  bend(hexy.left_middle, new_hip_angle = 0)
  bend(hexy.right_back, new_hip_angle = offset)
  
  sleep_hack()
  
  # Put tripod1 down
  neutral(hexy.right_front, new_hip_angle = -offset)
  neutral(hexy.left_middle, new_hip_angle = 0)
  neutral(hexy.right_back, new_hip_angle = offset)
  
  sleep_hack()

  # Raise tripod2 with appropriate hip angles
  bend(hexy.left_front, new_hip_angle = offset)
  bend(hexy.right_middle, new_hip_angle = 0)
  bend(hexy.left_back, new_hip_angle = -offset)
  
  sleep_hack()
  
  # Put tripod2 down
  neutral(hexy.left_front, new_hip_angle = offset)
  neutral(hexy.right_middle, new_hip_angle = 0)
  neutral(hexy.left_back, new_hip_angle = -offset)
  
  sleep_hack()


def rotate(offset = 35):
  # NOTE: Try offset = 35, -35 for clockwise and counterclockwise motion
  
  # Raise tripod1 legs while rotating respective hips
  for leg in tripod1:
    bend(leg, new_hip_angle = offset)
    
  sleep_hack()
  
  # Put down tripod1 legs
  for leg in tripod1:
    neutral(leg, new_hip_angle = offset)
  
  sleep_hack()
  
  # Raise tripod2 legs while rotating respective hips to other direction
  for leg in tripod2:
    bend(leg, new_hip_angle = -offset)
  
  # At the same time, 
  # Swing tripod1's hips while rotating respective hips to other direction
  for leg in tripod1: 
    leg.hip.pose(angle = -offset)
  
  sleep_hack()
  
  # Put down tripod2
  for leg in tripod2:
    neutral(leg, new_hip_angle = 0)
  
  sleep_hack()


def walk(swing = 15):
  # NOTE: Try swing = 15, -15 for backward and forward walk
  
  offset = 20
  hip1, hip2, hip3 = swing - offset, swing, -(offset + swing)
  
  # Replant tripod1 while tripod2 retracks / moves behind
  
  # ->raise tripod1 with respective hip movement
  bend(hexy.left_front, new_hip_angle = hip1)
  bend(hexy.right_middle, new_hip_angle = hip2)
  bend(hexy.left_back, new_hip_angle = hip3)
  
  # ->at the same time, swing tripod2 hips to the opposite direction
  neutral(hexy.right_front, new_hip_angle = hip3)
  neutral(hexy.left_middle, new_hip_angle = hip2)
  neutral(hexy.right_back, new_hip_angle = hip1)
  
  sleep_hack()
  
  # ->put tripod1 down to the floor
  neutral(hexy.left_front, new_hip_angle = hip1)
  neutral(hexy.right_middle, new_hip_angle = hip2)
  neutral(hexy.left_back, new_hip_angle = hip3)
  
  sleep_hack()

  # Replant tripod2 while tripod1 retracks / moves behind
 
  # ->raise tripod2 with respective hip movement
  bend(hexy.right_front, new_hip_angle = -hip1)
  bend(hexy.left_middle, new_hip_angle = -hip2)
  bend(hexy.right_back, new_hip_angle = -hip3)
 
  # ->at the same time, swing tripod1 hips to the opposite direction
  neutral(hexy.left_front, new_hip_angle = -hip3)
  neutral(hexy.right_middle, new_hip_angle = -hip2)
  neutral(hexy.left_back, new_hip_angle = -hip1)
  
  sleep_hack()
  
  # ->put tripod2 down to the floor
  neutral(hexy.right_front, new_hip_angle = -hip1)
  neutral(hexy.left_middle, new_hip_angle = -hip2)
  neutral(hexy.right_back, new_hip_angle = -hip3)
  
  sleep_hack()


def tilt_right():
  # NOTE: Assumes that in WALK_STANCE or TILT_LEFT prior to this
  offset = 35 
   
  bend(hexy.right_front, new_hip_angle = -offset) 
  bend(hexy.right_middle, new_hip_angle = 0) 
  bend(hexy.right_back, new_hip_angle = offset) 

  neutral(hexy.left_front, new_hip_angle = offset) 
  neutral(hexy.left_middle, new_hip_angle = 0) 
  neutral(hexy.left_back, new_hip_angle = -offset) 

  sleep_hack()


def tilt_left():
  # NOTE: Assumes that in WALK_STANCE or TILT_RIGHT prior to this
  offset = 35 
 
  neutral(hexy.right_front, new_hip_angle = -offset) 
  neutral(hexy.right_middle, new_hip_angle = 0) 
  neutral(hexy.right_back, new_hip_angle = offset) 

  bend(hexy.left_front, new_hip_angle = offset) 
  bend(hexy.left_middle, new_hip_angle = 0) 
  bend(hexy.left_back, new_hip_angle = -offset) 
  
  sleep_hack()


def squat():
  # NOTE: Assumes that in NEUTRAL_STANCE prior to this    
  
  for leg in hexy.legs:
    bend(leg, new_hip_angle = 0)

  sleep_hack()
  
  for leg in hexy.legs:
    neutral(leg, new_hip_angle = 0)
 
  sleep_hack()


def tiptoe():
  # NOTE: Assumes that in NEUTRAL_STANCE prior to this    
    
  for leg in hexy.legs:
    stretch(leg, new_hip_angle = 0)
 
  sleep_hack()

  for leg in hexy.legs:
    neutral(leg, new_hip_angle = 0)

  sleep_hack()

# --
# MOVEMENT FUNCTIONS
# --

def walk_forward(r = 5):
  
  for i in xrange(0, r):
    walk(swing = 15)
  
  do_neutral_stance()
    

def walk_backward(r = 5):
  
  for i in xrange(0, r):
    walk(swing = -15)
  
  do_neutral_stance()

  
def rotate_cw(r = 5):

  for i in xrange(0, r):
    rotate(offset = 35)
  
  do_neutral_stance()


def rotate_ccw(r = 5)

  for i in xrange(0, r):
    rotate(offset = -35)
  
  do_neutral_stance()


def squat_routine(r = 5):
  
  do_neutral_stance()

  for i in xrange(0, r):
    squat()


def tiptoe_routine(r = 5):
  
  do_neutral_stance()

  for i in xrange(0, r):
    tiptoe()


def dance_routine(r = 5):
  
  do_walk_stance()

  for i in xrange(0, r):
    tilt_left()
    tilt_right()
  
  do_neutral_stance()

# --
# MAIN
# --

do_neutral_stance()

while True:
  
  value = adc.read_adc_difference(0, gain = GAIN)
  # 0 = Channel 0 minus channel 1
  print value
  
  if value <= -5000:
    do_neutral_stance()
  
  if -5000 < value <= -4500:
    rotate_cw(r = 3)
  
  if -4500 < value <= 4000:
    rotate_ccw(r = 3)

  if -4000 < value <= 0:
    walk_forward(r = 5)

  if 0 < value <= 4000:
    walk_backward(r = 5)
  
  if 4000 < value <= 5000:
    squat_routine(r = 2)

  if 5000 < value <= 6000:
    tiptoe_routine(r = 2)
  
  if value > 6000:
    dance_routine(r = 3)
