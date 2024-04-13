from style_settings import (
    PAPER_BG_COLOR,
    LEGENDS_BG_COLOR,
    LEGEND_FONT_COLOR,
    AXIS_ZERO_LINE_COLOR,
    GROUND_COLOR,
    ARM_JOINT_COLORS,
    ARM_LINK_COLORS,
    BASE_LINK_COLOR,
    SHADOW_COLOR,
    ARM_LINK_SIZES_3D,
    BASE_LINK_SIZE,
)
from arm.templates.helpers import make_line_data3d, make_point_data3d
from arm.models import Vector, BASE_ARM

BASE_START_POINT = Vector(0, 0, 0, "base")
BASE_END_POINT = Vector(0, 0, 300, "base")
DZ = 1
OFFSET = BASE_ARM.length
points = BASE_ARM.all_points
shadow_points = [
    Vector(point.x, point.y, 0, f"shadow-{point.name}") for point in BASE_ARM.all_points
]

points_list = [
    make_point_data3d(p, c, h=OFFSET) for p, c in zip(points, ARM_JOINT_COLORS)
]

shadow_points_list = [make_point_data3d(p, SHADOW_COLOR, h=DZ) for p in shadow_points]

base_link = make_line_data3d(
    BASE_START_POINT, BASE_END_POINT, "base", BASE_LINK_COLOR, BASE_LINK_SIZE
)

links_list = [
    make_line_data3d(
        points[i],
        points[i + 1],
        f"link{i}",
        ARM_LINK_COLORS[i],
        ARM_LINK_SIZES_3D[i],
        OFFSET,
    )
    for i in range(3)
]

shadow_link_list = [
    make_line_data3d(
        shadow_points[i],
        shadow_points[i + 1],
        f"shadow-link{i}",
        SHADOW_COLOR,
        ARM_LINK_SIZES_3D[i],
    )
    for i in range(3)
]

data = [base_link] + links_list + points_list + shadow_link_list + shadow_points_list

BASE_FIGURE3D = {
    "data": data,
    "layout": {
        "paper_bgcolor": PAPER_BG_COLOR,
        "hovermode": "closest",
        "legend": {
            "x": 0,
            "y": 0,
            "bgcolor": LEGENDS_BG_COLOR,
            "font": {"family": "courier", "size": 12, "color": LEGEND_FONT_COLOR},
        },
        "margin": {"b": 20, "l": 10, "r": 10, "t": 20},
        "scene": {
            "aspectmode": "manual",
            "aspectratio": {"x": 1, "y": 1, "z": 1},
            "camera": {
                "up": {
                    "x": 0.00785039410388892,
                    "y": -0.006153976900953387,
                    "z": 0.9999502487027623,
                },
                "center": {
                    "x": 0.1044656684022553,
                    "y": -0.040142361584066734,
                    "z": -0.2647150399385452,
                },
                "eye": {
                    "x": 0.5952936378422042,
                    "y": 0.9515231973184444,
                    "z": 0.49360749511311613,
                },
                "projection": {"type": "perspective"},
            },
            "xaxis": {
                "nticks": 1,
                "range": [-OFFSET, OFFSET],
                "zerolinecolor": AXIS_ZERO_LINE_COLOR,
                "showbackground": False,
            },
            "yaxis": {
                "nticks": 1,
                "range": [-OFFSET, OFFSET],
                "zerolinecolor": AXIS_ZERO_LINE_COLOR,
                "showbackground": False,
            },
            "zaxis": {
                "nticks": 1,
                "range": [0, 2 * OFFSET],
                "zerolinecolor": AXIS_ZERO_LINE_COLOR,
                "showbackground": True,
                "backgroundcolor": GROUND_COLOR,
            },
        },
    },
}
