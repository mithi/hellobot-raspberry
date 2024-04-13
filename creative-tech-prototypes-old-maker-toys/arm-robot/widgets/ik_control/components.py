import dash_core_components as dcc
import dash_html_components as html
from dash.dependencies import Input

HEADER = html.Label(dcc.Markdown("**INVERSE KINEMATICS**"))
IK_PARAMS_DEFAULTS = [0.33, 0, 0.33]
IK_WIDGETS_IDS = [
    "widget-px",
    "widget-py",
    "widget-pz",
    "widget-bearing",
]
IK_CALLBACK_INPUTS = [Input(i, "value") for i in IK_WIDGETS_IDS]
