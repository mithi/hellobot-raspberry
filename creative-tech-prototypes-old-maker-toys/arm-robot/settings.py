"""
Set flags which will apply to the whole app globally
"""
DEBUG_MODE = True

# default dimensions
LINK1_DIMENSION = 100
LINK2_DIMENSION = 100
LINK3_DIMENSION = 100

# Too slow? set UPDATE_MODE='mouseup'
# Makes widgets only start updating when you release the mouse button
UPDATE_MODE = "drag"

# Make it more granular to prevent overloading the server
SLIDER_ANGLE_RESOLUTION = 0.25
INPUT_DIMENSIONS_RESOLUTION = 1

UI_GRAPH_HEIGHT = "600px"
UI_GRAPH_HEIGHT_HALF = "300px"
UI_GRAPH_WIDTH = "30%"
UI_CONTROLS_WIDTH = "17%"
