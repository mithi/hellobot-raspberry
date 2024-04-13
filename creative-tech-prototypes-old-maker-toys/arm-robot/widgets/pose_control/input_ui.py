"""
A page should import section of widgets for setting the angles
"""
import dash_core_components as dcc
import dash_html_components as html
from arm.models import VirtualArm
from style_settings import NUMBER_INPUT_STYLE
from widgets.section_maker import make_section_type4
from widgets.pose_control.components import POSE_WIDGET_IDS, HEADER


def make_input_field_widget(slider_id):
    return dcc.Input(
        id=slider_id,
        type="number",
        value=0,
        min=-180,
        max=180,
        step=1,
        style=NUMBER_INPUT_STYLE,
    )


def _code(name):
    return dcc.Markdown(f"`{name}`")


pose_widgets = [make_input_field_widget(id) for id in POSE_WIDGET_IDS]

row = make_section_type4(
    pose_widgets[0],
    pose_widgets[1],
    pose_widgets[2],
    pose_widgets[3],
    _code(VirtualArm.ANGLE_NAMES[0]),
    _code(VirtualArm.ANGLE_NAMES[1]),
    _code(VirtualArm.ANGLE_NAMES[2]),
    _code(VirtualArm.ANGLE_NAMES[3]),
)

POSE_WIDGETS_SECTION = html.Div([HEADER, row])
