import json
from dash.dependencies import Output, Input
import dash_html_components as html
from app import app
from widgets.dimensions_ui import DIMENSION_CALLBACK_INPUTS
from widgets.ik_control.components import IK_CALLBACK_INPUTS
# ......................
# Update arm dimensions callback
# ......................

DIMENSIONS_HIDDEN_SECTION_ID = "arm-dimensions-values"
DIMENSIONS_HIDDEN_SECTION = html.Div(
    id=DIMENSIONS_HIDDEN_SECTION_ID, style={"display": "none"}
)
DIMS_JSON_CALLBACK_INPUT = Input(DIMENSIONS_HIDDEN_SECTION_ID, "children")
DIMS_JSON_CALLBACK_OUTPUT = Output(DIMENSIONS_HIDDEN_SECTION_ID, "children")


@app.callback(DIMS_JSON_CALLBACK_OUTPUT, DIMENSION_CALLBACK_INPUTS)
def update_dimensions(link0, link1, link2):
    dimensions = {
        "link0": link0 or 0,
        "link1": link1 or 0,
        "link2": link2 or 0,
    }
    return json.dumps(dimensions)


# ......................
# Update inverse kinematics parameters
# ......................
IK_PARAMS_SECTION_ID = "hidden-params-ik"

OUTPUT = Output(IK_PARAMS_SECTION_ID, "children")
INPUTS = IK_CALLBACK_INPUTS


@app.callback(OUTPUT, INPUTS)
def update_ik_parameters(px, py, pz, bearing):
    ik_params = {
        "px": px or 0,
        "py": py or 0,
        "pz": pz or 0,
        "bearing": bearing or 0,
    }
    return json.dumps(ik_params)
