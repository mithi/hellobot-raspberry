"""
The Kinematics Page
"""
import json
from dash.dependencies import Output
from app import app
from widgets.pose_control.input_ui import POSE_WIDGETS_SECTION
from widgets.pose_control.components import POSE_CALLBACK_INPUTS
from pages import helpers
import pages.layouts.standard as page_layout
from arm.models import VirtualArm

GRAPH_ID_TOPVIEW = "graph-top-kinematics"
GRAPH_ID_SIDEVIEW = "graph-side-kinematics"
GRAPH_ID_3DVIEW = "graph-3d-kinematics"
PARAMS_SECTION_ID = "hidden-params-kinematics"
MESSAGE_SECTION_ID = "message-kinematics"


sidebar = page_layout.make_sidebar(
    POSE_WIDGETS_SECTION, PARAMS_SECTION_ID, MESSAGE_SECTION_ID
)

layout = page_layout.make_page_layout(
    GRAPH_ID_SIDEVIEW, GRAPH_ID_TOPVIEW, GRAPH_ID_3DVIEW, sidebar,
)

# ......................
# Update page
# ......................
outputs, inputs, states = page_layout.make_callback_params(
    GRAPH_ID_SIDEVIEW,
    GRAPH_ID_TOPVIEW,
    GRAPH_ID_3DVIEW,
    PARAMS_SECTION_ID,
    MESSAGE_SECTION_ID,
)


@app.callback(outputs, inputs, states)
def update_kinematics_page(
    dimensions_json,
    pose_json,
    relayout_side,
    relayout_top,
    relayout_3d,
    figure_side,
    figure_top,
    figure_3d,
):

    dimensions = helpers.load_params(dimensions_json, "dims")
    pose = helpers.load_params(pose_json, "pose")
    arm = VirtualArm(dimensions, pose)

    figures = [figure_side, figure_top, figure_3d]
    relayouts = [relayout_side, relayout_top, relayout_3d]
    helpers.update_figures(arm, figures, relayouts)

    return (
        figure_side,
        figure_top,
        figure_3d,
        helpers.make_points_message(arm.all_points),
    )


# ......................
# Update parameters
# ......................
OUTPUT = Output(PARAMS_SECTION_ID, "children")
INPUTS = POSE_CALLBACK_INPUTS


@app.callback(OUTPUT, INPUTS)
def update_pose(phi, alpha, beta, gamma):
    pose = {
        "phi": phi or 0,
        "alpha": alpha or 0,
        "beta": beta or 0,
        "gamma": gamma or 0,
    }
    return json.dumps(pose)
