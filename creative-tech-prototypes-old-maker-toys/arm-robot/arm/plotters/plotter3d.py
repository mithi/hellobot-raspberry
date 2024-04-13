from arm.models import Vector

BASE_START_POINT = Vector(0, 0, 0, "origin")


class ArmPlotter3d:
    def __init__(self):
        pass

    @staticmethod
    def update(fig, arm):
        ArmPlotter3d._draw_arm(fig, arm)
        ArmPlotter3d._draw_shadow(fig, arm)
        ArmPlotter3d._draw_scene(fig, arm)

    @staticmethod
    def change_view(fig, relayout_data):
        # camera = { 'up': {'x': 0, 'y': 0, 'z': 0},
        #        'center': {'x': 0, 'y': 0, 'z': 0},
        #           'eye': {'x': 0, 'y': 0, 'z': 0)}}
        if relayout_data and "scene.camera" in relayout_data:
            camera = relayout_data["scene.camera"]
            fig["layout"]["scene"]["camera"] = camera

    @staticmethod
    def _draw_line(fig, i, point1, point2, h):
        fig["data"][i]["x"] = [point1.x, point2.x]
        fig["data"][i]["y"] = [point1.y, point2.y]
        fig["data"][i]["z"] = [point1.z + h, point2.z + h]

    @staticmethod
    def _draw_point(fig, i, point, h):
        fig["data"][i]["x"] = [point.x]
        fig["data"][i]["y"] = [point.y]
        fig["data"][i]["z"] = [point.z + h]

    @staticmethod
    def _draw_arm(fig, arm):
        p = arm.all_points
        h = arm.length
        BASE_END_POINT = Vector(0, 0, h, "base")

        ArmPlotter3d._draw_line(fig, 0, BASE_START_POINT, BASE_END_POINT, 0)

        for i in range(1, 4):
            ArmPlotter3d._draw_line(fig, i, p[i - 1], p[i], h)

        for i, point in zip(range(4, 8), p):
            ArmPlotter3d._draw_point(fig, i, point, h)

    @staticmethod
    def _draw_shadow(fig, arm):
        DZ = 1
        p = [
            Vector(point.x, point.y, DZ, f"shadow-{point.name}")
            for point in arm.all_points
        ]
        for i in range(1, 4):
            ArmPlotter3d._draw_line(fig, 7 + i, p[i - 1], p[i], DZ)

        for i, point in zip(range(11, 15), p):
            ArmPlotter3d._draw_point(fig, i, point, DZ)

    @staticmethod
    def _draw_scene(fig, arm):
        fig["layout"]["scene"]["xaxis"]["range"] = [-arm.length, arm.length]
        fig["layout"]["scene"]["yaxis"]["range"] = [-arm.length, arm.length]
        fig["layout"]["scene"]["zaxis"]["range"] = [0, 2 * arm.length]
