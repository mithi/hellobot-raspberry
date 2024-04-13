import dash_core_components as dcc
import dash_html_components as html
from dash.dependencies import Input
from arm.models import VirtualArm

HEADER = html.Label(dcc.Markdown("**ARM ANGLES**"))
POSE_WIDGET_IDS = [f"widget-{angle}" for angle in VirtualArm.ANGLE_NAMES]
POSE_CALLBACK_INPUTS = [Input(i, "value") for i in POSE_WIDGET_IDS]
