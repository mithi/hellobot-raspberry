from arm.plotters.shared import change_view2d


class ArmPlotterSideView:
    def __init__(self):
        pass

    @staticmethod
    def update(fig, arm):
        ArmPlotterSideView._draw_arm(fig, arm)
        ArmPlotterSideView._draw_scene(fig, arm)

    @staticmethod
    def change_view(fig, relayout_data):
        change_view2d(fig, relayout_data)

    @staticmethod
    def _draw_line(fig, i, point1, point2):
        fig["data"][i]["x"] = [point1.x, point2.x]
        fig["data"][i]["y"] = [point1.z, point2.z]

    @staticmethod
    def _draw_point(fig, i, point):
        fig["data"][i]["x"] = [point.x]
        fig["data"][i]["y"] = [point.z]

    @staticmethod
    def _draw_arm(fig, arm):
        p = arm.all_points2d

        for i in range(0, 3):
            ArmPlotterSideView._draw_line(fig, i, p[i], p[i + 1])

        for i, point in zip(range(3, 7), p):
            ArmPlotterSideView._draw_point(fig, i, point)

    @staticmethod
    def _draw_scene(fig, arm):
        fig["layout"]["xaxis"]["range"] = [-1.2 * arm.get_link_len(0), arm.length]
        fig["layout"]["yaxis"]["range"] = [-arm.length, arm.length]
