"""
A page should import section of widgets
for setting the wrist point properties here
"""
import dash_html_components as html
import dash_daq
from settings import UPDATE_MODE
from style_settings import SLIDER_THEME, SLIDER_HANDLE_COLOR, SLIDER_COLOR
from widgets.ik_control.components import HEADER, IK_WIDGETS_IDS, IK_PARAMS_DEFAULTS
from widgets.ik_control.bearing_widget import BEARING_WIDGET


def make_slider(
    slider_id, param_default, slider_style, is_vert=True, min_val=-1, max_val=1, length=120
):
    _, label = slider_id.split("-")
    handle_style = {
        "showCurrentValue": True,
        "color": SLIDER_HANDLE_COLOR,
        "label": f"wrist.{label}",
    }

    daq_slider = dash_daq.Slider(  # pylint: disable=not-callable
        id=slider_id,
        min=min_val,
        max=max_val,
        value=param_default,
        step=0.01,
        size=length,
        updatemode=UPDATE_MODE,
        vertical=is_vert,
        handleLabel=handle_style,
        color={"default": SLIDER_COLOR},
        theme=SLIDER_THEME,
    )

    return html.Div(daq_slider, style=slider_style)


x_widget = make_slider(IK_WIDGETS_IDS[0], IK_PARAMS_DEFAULTS[0], {"padding": "3em 0 1em 3em"}, is_vert=False)

y_widget = make_slider(IK_WIDGETS_IDS[1], IK_PARAMS_DEFAULTS[1], {"padding": "1em 0 0 5em"})
z_widget = make_slider(IK_WIDGETS_IDS[2], IK_PARAMS_DEFAULTS[2],{"padding": "1em 0 0 5em"})

section_yz = html.Div([y_widget, z_widget], style={"display": "flex"})
section_xyz = html.Div(
    [x_widget, section_yz, BEARING_WIDGET], style={"fontFamily": "Courier New"},
)

IK_WIDGETS_SECTION = html.Div([HEADER, section_xyz])
