def tiptoe_tilt_right():
  # NOTE: Assumes that in WALK_STANCE or TILT_LEFT prior to this
  offset = 35

  neutral(hexy.right_front, new_hip_angle = -offset)
  neutral(hexy.right_middle, new_hip_angle = 0)
  neutral(hexy.right_back, new_hip_angle = offset)

  stretch(hexy.left_front, new_hip_angle = offset)
  stretch(hexy.left_middle, new_hip_angle = 0)
  stretch(hexy.left_back, new_hip_angle = -offset)

  sleep_hack()


def tiptoe_tilt_left():
  # NOTE: Assumes that in WALK_STANCE or TILT_RIGHT prior to this
  offset = 35

  stretch(hexy.right_front, new_hip_angle = -offset)
  stretch(hexy.right_middle, new_hip_angle = 0)
  stretch(hexy.right_back, new_hip_angle = offset)

  neutral(hexy.left_front, new_hip_angle = offset)
  neutral(hexy.left_middle, new_hip_angle = 0)
  neutral(hexy.left_back, new_hip_angle = -offset)

  sleep_hack()


def tiptoe_rotate(offset = 35):
  # NOTE: Try offset = 35, -35 for clockwise and counterclockwise motion

  # Raise tripod1 legs while rotating respective hips
  for leg in tripod1:
    bend(leg, new_hip_angle = offset)

  sleep_hack()

  # Put down tripod1 legs
  for leg in tripod1:
    stretch(leg, new_hip_angle = offset)

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
    stretch(leg, new_hip_angle = 0)

  sleep_hack()


def tiptoe_walk(swing = 15):
  # NOTE: Try swing = 15, -15 for backward and forward walk

  offset = 20
  hip1, hip2, hip3 = swing - offset, swing, -(offset + swing)

  # Replant tripod1 while tripod2 retracks / moves behind

  # ->raise tripod1 with respective hip movement
  bend(hexy.left_front, new_hip_angle = hip1)
  bend(hexy.right_middle, new_hip_angle = hip2)
  bend(hexy.left_back, new_hip_angle = hip3)

  # ->at the same time, swing tripod2 hips to the opposite direction
  stretch(hexy.right_front, new_hip_angle = hip3)
  stretch(hexy.left_middle, new_hip_angle = hip2)
  stretch(hexy.right_back, new_hip_angle = hip1)

  sleep_hack()

  # ->put tripod1 down to the floor
  stretch(hexy.left_front, new_hip_angle = hip1)
  stretch(hexy.right_middle, new_hip_angle = hip2)
  stretch(hexy.left_back, new_hip_angle = hip3)

  sleep_hack()

  # Replant tripod2 while tripod1 retracks / moves behind

  # ->raise tripod2 with respective hip movement
  bend(hexy.right_front, new_hip_angle = -hip1)
  bend(hexy.left_middle, new_hip_angle = -hip2)
  bend(hexy.right_back, new_hip_angle = -hip3)

  # ->at the same time, swing tripod1 hips to the opposite direction
  stretch(hexy.left_front, new_hip_angle = -hip3)
  stretch(hexy.right_middle, new_hip_angle = -hip2)
  stretch(hexy.left_back, new_hip_angle = -hip1)

  sleep_hack()

  # ->put tripod2 down to the floor
  stretch(hexy.right_front, new_hip_angle = -hip1)
  stretch(hexy.left_middle, new_hip_angle = -hip2)
  stretch(hexy.right_back, new_hip_angle = -hip3)

  sleep_hack()


def tiptoe_walk_forward(r = 5):

  for i in xrange(0, r):
    tiptoe_walk(swing = 15)

  do_neutral_stance()



def tiptoe_walk_backward(r = 5):

  for i in xrange(0, r):
    tiptoe_walk(swing = -15)

  do_neutral_stance()



def tiptoe_rotate_cw(r = 5):

  for i in xrange(0, r):
    tiptoe_rotate(offset = 35)

  do_neutral_stance()



def tiptoe_rotate_ccw(r = 5)

  for i in xrange(0, r):
    tiptoe_rotate(offset = -35)

  do_neutral_stance()

def tiptoe_dance_routine(r = 5):

  do_walk_stance()

  for i in xrange(0, r):
    tiptoe_tilt_left()
    tiptoe_tilt_right()

  do_neutral_stance()
