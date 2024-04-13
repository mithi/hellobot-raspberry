from style_settings import (
    PAPER_BG_COLOR,
    PLOT_BG_COLOR,
    ARM_LINK_COLORS,
    ARM_JOINT_COLORS,
    ARM_LINK_SIZES_2D,
)
from arm.templates.helpers import make_line_data2d, make_point_data2d
from arm.models import BASE_ARM

OFFSET = BASE_ARM.length
XNEG_OFFSET = -BASE_ARM.get_link_len(0)


def make_data_list(points, do_use_z=False):
    points_list = [
        make_point_data2d(p, c, use_z=do_use_z)
        for p, c in zip(points, ARM_JOINT_COLORS)
    ]

    links_list = [
        make_line_data2d(
            points[i],
            points[i + 1],
            f"link{i}",
            ARM_LINK_COLORS[i],
            ARM_LINK_SIZES_2D[i],
            do_use_z,
        )
        for i in range(3)
    ]
    return links_list + points_list


layout = {
    "plot_bgcolor": PLOT_BG_COLOR,
    "paper_bgcolor": PAPER_BG_COLOR,
    "hovermode": "closest",
    "xaxis": {"range": [0, OFFSET], "nticks": 1, "automargin": True},
    "yaxis": {
        "range": [-OFFSET, OFFSET],
        "nticks": 1,
        "scaleanchor": "x",
        "scaleratio": 1,
        "automargin": True,
    },
    "margin": {"l": 0, "r": 0, "t": 0, "b": 0},
}


data_side = make_data_list(BASE_ARM.all_points2d, do_use_z=True)
data_top = make_data_list(BASE_ARM.all_points, do_use_z=False)

BASE_FIGURE2D_TOP = {"data": data_top, "layout": layout}
BASE_FIGURE2D_SIDE = {"data": data_side, "layout": layout}
