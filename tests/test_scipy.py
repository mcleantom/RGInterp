from rgi_interp_python import *
import numpy as np
from scipy.interpolate import RegularGridInterpolator
from unittest import TestCase
from timeit import Timer


def f(x, y, z):
    return 2 * x**3 + 3 * y**2 - z


class TestScipyExample(TestCase):

    def test_scipy_example(self):
        x = np.linspace(1, 4, 11)
        y = np.linspace(4, 7, 22)
        z = np.linspace(7, 9, 33)
        xg, yg, zg = np.meshgrid(x, y, z, indexing='ij', sparse=True)
        data = f(xg, yg, zg)

        interpolator = LinearInterpolator3D(
            CoordinateAxis(1, 4, 11),
            CoordinateAxis(4, 7, 22),
            CoordinateAxis(7, 9, 33),
            Grid3D(data, float("inf"), "Data")
        )

        res = interpolator.interpolate([2.1, 3.3], [6.2, 5.2], [8.3, 7.1])
        expected_res = [125.80469388,  146.30069388]

        self.assertEqual(len(res), len(expected_res))

        for got, expected in zip(res, expected_res):
            self.assertAlmostEqual(got, expected)

    def test_speed(self):
        x = np.linspace(1, 4, 11)
        y = np.linspace(4, 7, 22)
        z = np.linspace(7, 9, 33)
        xg, yg, zg = np.meshgrid(x, y, z, indexing='ij', sparse=True)
        data = f(xg, yg, zg)

        scipy_rgi = RegularGridInterpolator([x, y, z], data, method="linear")

        rgi_interp = LinearInterpolator3D(
            CoordinateAxis(1, 4, 11),
            CoordinateAxis(4, 7, 22),
            CoordinateAxis(7, 9, 33),
            Grid3D(data, float("inf"), "Data")
        )

        N = int(1e7)
        x_test = np.linspace(1, 4, N)
        y_test = np.linspace(4, 7, N)
        z_test = np.linspace(7, 9, N)
        test_points = np.vstack((x_test, y_test, z_test)).T

        n_starts = 1
        scipy_timer = Timer(lambda: scipy_rgi(test_points)).timeit(number=n_starts)
        rgi_interp_timer = Timer(lambda: rgi_interp.interpolate(x_test, y_test, z_test)).timeit(number=n_starts)

        pass
