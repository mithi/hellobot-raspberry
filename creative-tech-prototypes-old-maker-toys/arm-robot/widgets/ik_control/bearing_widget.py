import dash_daq
import dash_html_components as html
from settings import UPDATE_MODE
from style_settings import SLIDER_THEME, SLIDER_HANDLE_COLOR, SLIDER_COLOR
from widgets.ik_control.components import IK_WIDGETS_IDS

wrist_targets = {
    "0": {"label": "point.forward\n."},
    "1": {"label": "point.down\n."},
}

BEARING_WIDGET = html.Div(
    dash_daq.Slider(  # pylint: disable=not-callable
        id=IK_WIDGETS_IDS[3],
        min=0,
        max=1,
        value=1,
        step=1,
        size=120,
        updatemode=UPDATE_MODE,
        handleLabel={"color": SLIDER_HANDLE_COLOR, "label": "orientation"},
        targets=wrist_targets,
        color={"default": SLIDER_COLOR},
        theme=SLIDER_THEME,
        labelPosition="bottom",
    ),
    style={"padding": "3em 0 2em 3em"},
)
