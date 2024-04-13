from arm.models import (
    BASE_ARM,
    BASE_POSE,
    BASE_DIMENSIONS,
)  # pylint: disable=unused-import
from arm.templates.figure_2d_template import (
    BASE_FIGURE2D_SIDE,
    BASE_FIGURE2D_TOP,
)  # pylint: disable=unused-import
from arm.templates.figure_3d_template import (
    BASE_FIGURE3D,
)  # pylint: disable=unused-import
from arm.plotters.plotter2d_side import ArmPlotterSideView
from arm.plotters.plotter2d_top import ArmPlotterTopView
from arm.plotters.plotter3d import ArmPlotter3d

BASE_SIDEVIEW_PLOTTER = ArmPlotterSideView()
BASE_TOPVIEW_PLOTTER = ArmPlotterTopView()
BASE_3DVIEW_PLOTTER = ArmPlotter3d()

BASE_IK_PARAMS = {
    "px": 0.33,
    "py": 0,
    "pz": 0.33,
    "bearing": 0,
}
