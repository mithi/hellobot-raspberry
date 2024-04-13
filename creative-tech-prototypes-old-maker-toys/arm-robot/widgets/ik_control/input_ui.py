import dash_core_components as dcc
import dash_html_components as html
from style_settings import NUMBER_INPUT_STYLE
from widgets.section_maker import make_section_type3
from widgets.ik_control.components import HEADER, IK_WIDGETS_IDS, IK_PARAMS_DEFAULTS
from widgets.ik_control.bearing_widget import BEARING_WIDGET



def make_input_field_widget(widget_id, default):
    return dcc.Input(
        id=widget_id,
        type="number",
        value=default,
        min=-1.0,
        max=1.0,
        step=0.01,
        style=NUMBER_INPUT_STYLE,
    )


def _code(name):
    return dcc.Markdown(f"`{name}`")


widgets = [
    make_input_field_widget(_id, _default)
    for _id, _default in zip(IK_WIDGETS_IDS, IK_PARAMS_DEFAULTS)
]

xyz_widgets_row = make_section_type3(
    widgets[0], widgets[1], widgets[2], _code("px"), _code("py"), _code("pz"),
)

IK_WIDGETS_SECTION = html.Div([HEADER, xyz_widgets_row, BEARING_WIDGET])
