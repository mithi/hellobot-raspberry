from math import degrees, sqrt, atan2, sin, cos, radians
from numpy import arccos

POINT_FORWARD = 0
POINT_DOWN = 1


def angle_opposite_of_last_side(a, b, c):
    ratio = (a * a + b * b - c * c) / (2 * a * b)
    return degrees(arccos(ratio))


def is_triangle(a, b, c):
    return (a + b > c) and (a + c > b) and (b + c > a)


def solve_ik(dimensions, ik_params, in_percent=True):
    return IKSolver(dimensions, ik_params, in_percent).pose()


class IKSolver:
    def __init__(self, dimensions, ik_params, in_percent=False):
        # (x, y, z) is the target wrist point

        self.dimensions = dimensions
        self.ik_params = ik_params

        self.link0 = dimensions["link0"]
        self.link1 = dimensions["link1"]
        self.link2 = dimensions["link2"]
        self.length = self.link0 + self.link1 + self.link2
        self._store_target_points(in_percent)

        self.bearing = ik_params["bearing"]
        self.points_on_a_line = False


        self.phi = degrees(atan2(self.y, self.x))
        # IMPORTANT: Because of this x_ is always positive
        self.x_ = sqrt(self.x * self.x + self.y * self.y)

        # wrist_dist - distance from origin to target wrist point
        self.wrist_dist = sqrt(self.x_ * self.x_ + self.z * self.z)

        if not is_triangle(self.link0, self.wrist_dist, self.link1):
            msg = f"link0, link1, and target_distance can't form a triangle.\n\
                {self.link0} | {self.link1} | {self.wrist_dist}"
            raise Exception(msg)

        self._check_if_all_points_on_one_line_case()
        if self.points_on_a_line is False:
            self._compute_alpha()
            self._compute_beta()

        self._compute_gamma()

    def _store_target_points(self, in_percent):
        if in_percent is True:
            self.x = self.ik_params["px"] * self.length
            self.y = self.ik_params["py"] * self.length
            self.z = self.ik_params["pz"] * self.length
        else:
            self.x = self.ik_params["px"]
            self.y = self.ik_params["py"]
            self.z = self.ik_params["pz"]

    def _check_if_all_points_on_one_line_case(self):
        cond1 = self.link0 + self.link1 == self.wrist_dist
        cond2 = self.link0 - self.link1 == self.wrist_dist
        cond3 = self.link1 - self.link0 == self.wrist_dist

        if cond1 or cond2 or cond3:
            self.points_on_a_line = True
            self.alpha = degrees(atan2(self.z, self.x_)) - 90
            if cond1:
                self.beta = 0
            else:
                self.beta = -180

    def _compute_alpha(self):

        # angle between x_ axis
        # and vector pointing to wrist target
        angle1 = degrees(atan2(self.z, self.x_))

        # angle between link0 and
        # vector pointing to wrist target
        angle2 = angle_opposite_of_last_side(self.link0, self.wrist_dist, self.link1)
        self.alpha = angle1 + angle2 - 90

    def _compute_beta(self):
        # angle between link0 and link1
        angle = angle_opposite_of_last_side(self.link0, self.link1, self.wrist_dist)
        self.beta = angle - 90

    def _compute_gamma(self):
        if self.bearing == POINT_DOWN:
            xtip = self.x_
            ztip = self.z - self.link2
        else:
            # point forward
            xtip = self.x_ + self.link2
            ztip = self.z

        if self.bearing == POINT_FORWARD and self.z < 0:
            p1z = self.link0 * cos(radians(-self.alpha))
            p1x = self.link0 * sin(radians(-self.alpha))
            dist = sqrt((p1x - xtip) ** 2 + (p1z - ztip) ** 2)
            angle = angle_opposite_of_last_side(self.link1, self.link2, dist)
            self.gamma = 180 - angle
            return

        tip_dist = sqrt(xtip * xtip + ztip * ztip)
        angle1 = angle_opposite_of_last_side(self.wrist_dist, self.link1, self.link0)
        angle2 = angle_opposite_of_last_side(self.wrist_dist, self.link2, tip_dist)
        self.gamma = angle1 + angle2 - 180

    def pose(self):
        return {
            "phi": self.phi,
            "alpha": self.alpha,
            "beta": self.beta,
            "gamma": self.gamma,
        }
