from itertools import product
from arm.models import VirtualArm, BASE_DIMENSIONS
from random import sample, choices

selected_angles = [-90, -60, -45, -30, 0, 30, 45, 60, 90]


def all_cases():
    for i, angles in enumerate(product(selected_angles, repeat=4)):
        phi, alpha, beta, gamma = angles
        pose = {"phi": phi, "alpha": alpha, "beta": beta, "gamma": gamma}
        print(f"Case # {i} > {pose}")
        print(VirtualArm(BASE_DIMENSIONS, pose).get_point(2))


def random_case():
    phi, alpha, beta, gamma = choices(selected_angles, k=4)
    pose = {"phi": phi, "alpha": alpha, "beta": beta, "gamma": gamma}
    print(pose)
    print(VirtualArm(BASE_DIMENSIONS, pose).get_point(2))


random_case()
