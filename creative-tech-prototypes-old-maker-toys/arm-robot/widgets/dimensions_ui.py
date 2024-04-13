"""
A page should import section of widgets for setting the dimensions here
"""
import dash_core_components as dcc
import dash_html_components as html
from dash.dependencies import Input
from settings import (
    INPUT_DIMENSIONS_RESOLUTION,
    LINK1_DIMENSION,
    LINK2_DIMENSION,
    LINK3_DIMENSION,
)
from style_settings import NUMBER_INPUT_STYLE
from arm.models import VirtualArm
from widgets.section_maker import make_section_type3


def make_positive_number_input(_name, _value):
    """Returns a widget for positive number inputs"""
    return dcc.Input(
        id=_name,
        type="number",
        value=_value,
        min=0,
        step=INPUT_DIMENSIONS_RESOLUTION,
        style=NUMBER_INPUT_STYLE,
    )


def _code(name):
    """returns html label with monospace text"""
    return dcc.Markdown(f"`{name}`")


# ......................
# Components
# ......................


HEADER = html.Label(dcc.Markdown("**ARM ROBOT DIMENSIONS**"))

DIMENSION_WIDGET_IDS = [
    "widget-dimension-link0",
    "widget-dimension-link1",
    "widget-dimension-link2",
]

DIMENSION_CALLBACK_INPUTS = [Input(id, "value") for id in DIMENSION_WIDGET_IDS]
link1_input = make_positive_number_input(DIMENSION_WIDGET_IDS[0], LINK1_DIMENSION)
link2_input = make_positive_number_input(DIMENSION_WIDGET_IDS[1], LINK2_DIMENSION)
link3_input = make_positive_number_input(DIMENSION_WIDGET_IDS[2], LINK3_DIMENSION)

sections = make_section_type3(
    link1_input,
    link2_input,
    link3_input,
    _code(VirtualArm.LINK_NAMES[0]),
    _code(VirtualArm.LINK_NAMES[1]),
    _code(VirtualArm.LINK_NAMES[2]),
)

DIMENSION_WIDGETS_SECTION = html.Div(
    [HEADER, html.Div(sections, style={"display": "flex"}), html.Br()]
)
