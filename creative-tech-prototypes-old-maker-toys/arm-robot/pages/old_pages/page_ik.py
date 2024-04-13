"""
The Inverse Kinematics Page
"""
import json
from dash.dependencies import Output
from widgets.ik_control.input_ui import IK_WIDGETS_SECTION
from widgets.ik_control.components import IK_CALLBACK_INPUTS
from pages import helpers
import pages.layouts.standard as page_layout
from pages.shared import IK_PARAMS_SECTION_ID

from arm.models import VirtualArm
from arm.ik_solver import solve_ik
from app import app

GRAPH_ID_TOPVIEW = "graph-top-ik"
GRAPH_ID_SIDEVIEW = "graph-side-ik"
GRAPH_ID_3DVIEW = "graph-3d-ik"
PARAMS_SECTION_ID = IK_PARAMS_SECTION_ID
MESSAGE_SECTION_ID = "message-ik"


sidebar = page_layout.make_sidebar(
    IK_WIDGETS_SECTION, PARAMS_SECTION_ID, MESSAGE_SECTION_ID
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
    ik_params_json,
    relayout_side,
    relayout_top,
    relayout_3d,
    figure_side,
    figure_top,
    figure_3d,
):

    dimensions = helpers.load_params(dimensions_json, "dims")
    ik_params = helpers.load_params(ik_params_json, "ik")

    try:
        pose = solve_ik(dimensions, ik_params)
    except Exception as alert:
        return (
            figure_side,
            figure_top,
            figure_3d,
            str(alert),
        )

    arm = VirtualArm(dimensions, pose)

    figures = [figure_side, figure_top, figure_3d]
    relayouts = [relayout_side, relayout_top, relayout_3d]
    helpers.update_figures(arm, figures, relayouts)

    return (
        figure_side,
        figure_top,
        figure_3d,
        helpers.make_pose_message(pose, arm.get_point(2)),
    )