import json
import dash_core_components as dcc
from arm.const import (
    BASE_DIMENSIONS,
    BASE_POSE,
    BASE_IK_PARAMS,
    BASE_3DVIEW_PLOTTER,
    BASE_SIDEVIEW_PLOTTER,
    BASE_TOPVIEW_PLOTTER,
)


def make_monospace(text):
    return dcc.Markdown(f" ```{text}")


def make_points_message(points):
    msg = ""

    for point in points[1:]:
        msg += f"\n{point.name}:"
        msg += f"\n > x: {point.x:<+10.2f}"
        msg += f"\n > y: {point.y:<+10.2f}"
        msg += f"\n > z: {point.z:<+10.2f}"

    return make_monospace(msg)


def make_pose_message(pose, tip):
    msg = ""

    for name, angle in pose.items():
        msg += f"\n{name:6}: {angle:<+10.2f}"

    msg += f"\n\n{tip.name}:"
    msg += f"\n > x: {tip.x:<+10.2f}"
    msg += f"\n > y: {tip.y:<+10.2f}"
    msg += f"\n > z: {tip.z:<+10.2f}"

    return make_monospace(msg)


def load_params(params_json, params_type):
    try:
        params = json.loads(params_json)
    except Exception as e:

        print(f"Error loading json of type {params_type}. {e} | {params_json}")

        if params_type == "dims":
            return BASE_DIMENSIONS
        elif params_type == "pose":
            return BASE_POSE
        elif params_type == "ik":
            return BASE_IK_PARAMS

        raise Exception(f"Can't handle json of type: {params_type}")

    return params


def update_figures(arm, figures, relayouts):
    PLOTTERS = [BASE_SIDEVIEW_PLOTTER, BASE_TOPVIEW_PLOTTER, BASE_3DVIEW_PLOTTER]
    for plotter, figure, relayout in zip(PLOTTERS, figures, relayouts):
        plotter.update(figure, arm)
        plotter.change_view(figure, relayout)
