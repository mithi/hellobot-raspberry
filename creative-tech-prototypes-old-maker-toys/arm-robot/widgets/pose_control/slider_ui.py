"""
A page should import section of widgets for setting the angles
"""
import dash_core_components as dcc
import dash_html_components as html
from dash.dependencies import Input
import dash_daq
from settings import (
    UPDATE_MODE,
    SLIDER_ANGLE_RESOLUTION,
)
from style_settings import SLIDER_THEME, SLIDER_HANDLE_COLOR, SLIDER_COLOR
from widgets.pose_control.components import POSE_WIDGET_IDS, HEADER


def make_slider(slider_id, min_angle=-180, max_angle=180):
    _, theta = slider_id.split("-")

    handle_style = {
        "showCurrentValue": True,
        "color": SLIDER_HANDLE_COLOR,
        "label": theta,
    }

    daq_slider = dash_daq.Slider(  # pylint: disable=not-callable
        id=slider_id,
        min=min_angle,
        max=max_angle,
        value=1.5,
        step=SLIDER_ANGLE_RESOLUTION,
        size=120,
        updatemode=UPDATE_MODE,
        handleLabel=handle_style,
        color={"default": SLIDER_COLOR},
        theme=SLIDER_THEME,
    )

    return html.Div(
        daq_slider, style={"padding": "2.5em 0 0.5em 2em", "fontFamily": "Courier New"}
    )


pose_widgets = [make_slider(id) for id in POSE_WIDGET_IDS]
POSE_WIDGETS_SECTION = html.Div([HEADER] + pose_widgets)
