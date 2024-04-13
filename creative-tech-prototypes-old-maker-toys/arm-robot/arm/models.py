from collections import namedtuple
from math import sin, cos, radians
import numpy as np

BASE_DIMENSIONS = {"link0": 100, "link1": 100, "link2": 100}
BASE_POSE = {"phi": 0, "alpha": 0, "beta": 0, "gamma": 0}

Vector = namedtuple("Vector", "x y z name")

#  z axis
#  ^
#  |
#  | /
#  |/ yaxis
#  |-------> x axis
# origin
#
# If: phi = 0 alpha = 0, beta = 0, gamma = 0
# Then: The arm should look like this:
#
#  p1    p2     p3
#  * -----*-----*
#  |
#  |
#  p0


def rotated_point(point, frame):
    p = np.array([point.x, point.y, point.z, 1])
    p = np.matmul(frame, p)
    return Vector(p[0], p[1], p[2], point.name)


def rotz(theta):
    c, s = _return_sin_and_cos(theta)
    return np.array([[c, -s, 0, 0], [s, c, 0, 0], [0, 0, 1, 0], [0, 0, 0, 1]])


def vector_from_to(a, b):
    """get vector pointing from point a to point b"""
    return Vector(b.x - a.x, b.y - a.y, b.z - a.z, None)


def _return_sin_and_cos(theta):
    d = radians(theta)
    c = cos(d)
    s = sin(d)
    return c, s


class VirtualArm:
    LINK_NAMES = ("link0", "link1", "link2")
    ANGLE_NAMES = ("phi", "alpha", "beta", "gamma")
    POINT_NAMES = ("shoulder-joint", "elbow-joint", "wrist-joint", "tip")
    __slots__ = (
        "dimensions",
        "pose",
        "all_points2d",
        "all_points",
        "length",
        "ranges",
    )

    def __init__(self, dimensions=BASE_DIMENSIONS, pose=BASE_POSE):
        self.dimensions = dimensions
        self.pose = pose
        self.all_points2d = []
        self.all_points = []
        self.length = sum(dimensions.values())
        self.ranges = {}
        self._populate_points()
        self._populate_ranges()

    def get_point(self, i):
        return self.all_points[i]

    def get_point2d(self, i):
        return self.all_points2d[i]

    def get_link_len(self, i):
        return self.dimensions[VirtualArm.LINK_NAMES[i]]

    def get_link_vec(self, i):
        p1 = self.all_points[i]
        p2 = self.all_points[i + 1]
        return vector_from_to(p1, p2)

    def get_angle(self, i):
        return self.pose[VirtualArm.ANGLE_NAMES[i]]

    def _populate_points(self):
        link0 = self.dimensions["link0"]
        link1 = self.dimensions["link1"]
        link2 = self.dimensions["link2"]

        phi = self.pose["phi"]
        alpha = self.pose["alpha"]
        beta = self.pose["beta"]
        gamma = self.pose["gamma"]

        alpha_ = alpha + 90
        beta_ = (beta - 90) + alpha_
        gamma_ = beta_ + gamma

        p0 = Vector(0, 0, 0, "shoulder-joint")

        p1x = link0 * cos(radians(alpha_))
        p1z = link0 * sin(radians(alpha_))
        p1 = Vector(p1x, 0, p1z, "elbow-joint")

        p2x = p1x + link1 * cos(radians(beta_))
        p2z = p1z + link1 * sin(radians(beta_))
        p2 = Vector(p2x, 0, p2z, "wrist-joint")

        p3x = p2x + link2 * cos(radians(gamma_))
        p3z = p2z + link2 * sin(radians(gamma_))
        p3 = Vector(p3x, 0, p3z, "tip-joint")

        twist = rotz(phi)

        self.all_points2d = [p0, p1, p2, p3]
        self.all_points = [rotated_point(p, twist) for p in self.all_points2d]

    def _populate_ranges(self):

        min_x2d = min([p.x for p in self.all_points2d])
        max_x2d = max([p.x for p in self.all_points2d])

        min_z2d = min([p.z for p in self.all_points2d])
        max_z2d = max([p.z for p in self.all_points2d])

        min_x = min([p.x for p in self.all_points])
        max_x = max([p.x for p in self.all_points])

        min_y = min([p.y for p in self.all_points2d])
        max_y = max([p.y for p in self.all_points2d])

        min_z = min([p.z for p in self.all_points])
        max_z = max([p.z for p in self.all_points])

        self.ranges = {
            "x": (min_x, max_x),
            "y": (min_y, max_y),
            "z": (min_z, max_z),
            "x2d": (min_x2d, max_x2d),
            "z2d": (min_z2d, max_z2d),
        }


BASE_ARM = VirtualArm(BASE_DIMENSIONS, BASE_POSE)
