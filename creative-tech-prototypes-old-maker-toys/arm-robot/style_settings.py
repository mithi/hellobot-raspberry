"""
Configure the colors, sizes and other page stylings
"""
DARKMODE = True

DARK_CSS_PATH = "https://codepen.io/mithi-the-encoder/pen/BaoBOKa.css"
LIGHT_CSS_PATH = "https://codepen.io/mithi-the-encoder/pen/eYpObwK.css"

EXTERNAL_STYLESHEETS = [DARK_CSS_PATH]
if not DARKMODE:
    EXTERNAL_STYLESHEETS = [LIGHT_CSS_PATH]

# ***************************************
# GLOBAL PAGE STYLE
# ***************************************

DARK_BG_COLOR = "#222f3e"
DARK_FONT_COLOR = "#32ff7e"

GLOBAL_PAGE_STYLE = {
    "background": DARK_BG_COLOR,
    "color": DARK_FONT_COLOR,
    "padding": "0em",
}

if not DARKMODE:
    GLOBAL_PAGE_STYLE = {"background": "#ffffff", "color": "#2c3e50", "padding": "0em"}


# ***************************************
# NUMBER FIELD INPUT WIDGET
# ***************************************

NUMBER_INPUT_STYLE = {
    "marginRight": "5%",
    "width": "95%",
    "marginBottom": "5%",
    "borderRadius": "10px",
    "border": "solid 1px",
    "fontFamily": "Courier New",
}

if DARKMODE:
    NUMBER_INPUT_STYLE["backgroundColor"] = "#2c3e50"
    NUMBER_INPUT_STYLE["color"] = "#2ecc71"
    NUMBER_INPUT_STYLE["borderColor"] = "#2980b9"


# ***************************************
# DAQ SLIDER INPUT WIDGET
# ***************************************

IK_SLIDER_SIZE = 100

SLIDER_THEME = {
    "dark": DARKMODE,
    "detail": "#ffffff",
    "primary": "#ffffff",
    "secondary": "#ffffff",
}

SLIDER_HANDLE_COLOR = "#2ecc71"
SLIDER_COLOR = "#FC427B"

if not DARKMODE:
    SLIDER_HANDLE_COLOR = "#2c3e50"
    SLIDER_COLOR = "#8e44ad"

# ***************************************
# GRAPH STYLES
# ***************************************

ORANGE = "#ffa801"
PINK = "#ef5777"
DARK_RED = "#d63031"
DARK_PINK = "#e84393"
LIGHT_GREEN = "#2ecc71"
LIGHT_GREEN_TRANSPARENT = "rgba(46,204,113, 0.5)"

JOINT_SIZE_2D = 12
JOINT_SIZE_3D = 15
ARM_LINK_SIZES_2D = [9, 5, 9]
ARM_LINK_SIZES_3D = [15, 8, 15]
BASE_LINK_SIZE = 3
ARM_JOINT_COLORS = [LIGHT_GREEN_TRANSPARENT, ORANGE, ORANGE, LIGHT_GREEN]
ARM_LINK_COLORS = [DARK_PINK, PINK, DARK_PINK]
BASE_LINK_COLOR = LIGHT_GREEN
SHADOW_COLOR = "#222f3e"


PAPER_BG_COLOR = "#222f3e"
PLOT_BG_COLOR = "#222f3e"

LEGENDS_BG_COLOR = "rgba(44, 62, 80, 0.8)"
AXIS_ZERO_LINE_COLOR = "#079992"
PAPER_BG_COLOR = "#222f3e"
GROUND_COLOR = "#0a3d62"
LEGEND_FONT_COLOR = "#2ecc71"

if not DARKMODE:
    LEGENDS_BG_COLOR = "rgba(255, 255, 255, 0.5)"
    AXIS_ZERO_LINE_COLOR = "#ffa801"
    PAPER_BG_COLOR = "white"
    PLOT_BG_COLOR = "white"
    GROUND_COLOR = "rgb(240, 240, 240)"
    LEGEND_FONT_COLOR = "#34495e"
