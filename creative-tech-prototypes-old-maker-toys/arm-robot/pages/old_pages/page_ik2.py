"""
The Inverse Kinematics Page
"""
import json
from dash.dependencies import Output
from widgets.ik_control.input_ui import IK_WIDGETS_SECTION
from widgets.ik_control.components import IK_CALLBACK_INPUTS
from arm.const import BASE_FIGURE3D, BASE_3DVIEW_PLOTTER
from pages import helpers
import pages.layouts.bare as page_layout
from pages.layouts.standard import make_sidebar
from pages.shared import IK_PARAMS_SECTION_ID

from arm.models import VirtualArm
from arm.ik_solver import solve_ik
from app import app

GRAPH_ID = "graph-3d-ik-2"
PARAMS_SECTION_ID = IK_PARAMS_SECTION_ID
MESSAGE_SECTION_ID = "message-ik-2"


sidebar = make_sidebar(
    IK_WIDGETS_SECTION, PARAMS_SECTION_ID, MESSAGE_SECTION_ID
)

layout = page_layout.make_page_layout(
   GRAPH_ID, sidebar, BASE_FIGURE3D
)
# ......................
# Update page
# ......................
outputs, inputs, states = page_layout.make_callback_params(
    GRAPH_ID,
    PARAMS_SECTION_ID,
    MESSAGE_SECTION_ID,
)


@app.callback(outputs, inputs, states)
def update_ik2_page(
    dimensions_json,
    ik_params_json,
    relayout_data,
    figure,
):

    dimensions = helpers.load_params(dimensions_json, "dims")
    ik_params = helpers.load_params(ik_params_json, "ik")
    print(f"dimensions: {dimensions}, ik: {ik_params}")
    try:
        pose = solve_ik(dimensions, ik_params)
    except Exception as alert:
        return figure, str(alert)

    arm = VirtualArm(dimensions, pose)

    BASE_3DVIEW_PLOTTER.update(figure, arm)
    BASE_3DVIEW_PLOTTER.change_view(figure, relayout_data)

    return (
        figure,
        helpers.make_pose_message(pose, arm.get_point(2)),
    )


