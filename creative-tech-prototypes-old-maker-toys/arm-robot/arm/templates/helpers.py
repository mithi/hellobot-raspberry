from style_settings import JOINT_SIZE_2D, JOINT_SIZE_3D


def make_point_data3d(point, color, size=JOINT_SIZE_3D, h=0, show_legend=False):
    return {
        "marker": {"color": color, "size": size},
        "mode": "markers",
        "name": point.name,
        "type": "scatter3d",
        "x": [point.x],
        "y": [point.y],
        "z": [point.z + h],
        "showlegend": show_legend,
    }


def make_line_data3d(
    point1, point2, name, color, size=JOINT_SIZE_3D, h=0, show_legend=False
):
    return {
        "line": {"color": color, "width": size},
        "name": name,
        "type": "scatter3d",
        "x": [point1.x, point2.x],
        "y": [point1.y, point2.y],
        "z": [point1.z + h, point2.z + h],
        "hoverinfo": "skip",
        "showlegend": show_legend,
    }


def make_point_data2d(point, color, size=JOINT_SIZE_2D, use_z=False):
    if use_z:
        y = point.z
    else:
        y = point.y

    return {
        "x": [point.x],
        "y": [y],
        "name": point.name,
        "mode": "markers",
        "marker": {"size": size, "color": color},
        "showlegend": False,
    }


def make_line_data2d(point1, point2, name, color, size=JOINT_SIZE_2D, use_z=False):
    if use_z:
        y1, y2 = point1.z, point2.z
    else:
        y1, y2 = point1.y, point2.y

    return {
        "x": [point1.x, point2.x],
        "y": [y1, y2],
        "line": {"color": color, "width": size},
        "name": name,
        "showlegend": False,
        "hoverinfo": "skip",
    }
