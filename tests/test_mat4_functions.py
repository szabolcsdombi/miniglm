import unittest

from math import cos, sin
from miniglm import mat4_look_at, mat4_ortho, mat4_perspective, radians
from common import MyTestCase


class TestCase(MyTestCase):
    def test_mat4_perspective(self):
        projection = mat4_perspective(radians(90), 1.0, 1.0, 10.0)
        self.assertAlmostEqual2(projection, (1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, -1.222222, -1.0, 0.0, 0.0, -2.222222, 0.0))

        projection = mat4_perspective(radians(90), 2.0, 1.0, 10.0)
        self.assertAlmostEqual2(projection, (0.5, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, -1.222222, -1.0, 0.0, 0.0, -2.222222, 0.0))

        projection = mat4_perspective(radians(60), 1.5, 1.0, 10.0)
        self.assertAlmostEqual2(projection, (1.154700, 0.0, 0.0, 0.0, 0.0, 1.732050, 0.0, 0.0, 0.0, 0.0, -1.222222, -1.0, 0.0, 0.0, -2.222222, 0.0))

        projection = mat4_perspective(radians(60), 1.5, 0.1, 100.0)
        self.assertAlmostEqual2(projection, (1.154700, 0.0, 0.0, 0.0, 0.0, 1.732050, 0.0, 0.0, 0.0, 0.0, -1.002002, -1.0, 0.0, 0.0, -0.200200, 0.0))

    def test_mat4_look_at(self):
        a = mat4_look_at(
            (cos(0.5) * 5.0, sin(0.5) * 5.0, 2.0),
            (0.0, 0.0, 0.5),
            (0.0, 0.0, 1.0)
        )
        self.assertAlmostEqual2(a, (-0.479425, -0.252171, 0.840571, 0.0, 0.877582, -0.137761, 0.459206, 0.0, 0.0, 0.957826, 0.287347, 0.0, 0.0, -0.478913, -5.363826, 1.0))

    def test_mat4_ortho(self):
        a = mat4_ortho(-1.0, 1.0, 1.0, -1.0, 1.0, 1000.0)
        self.assertAlmostEqual2(a, (1.0, 0.0, 0.0, 0.0, 0.0, -1.0, 0.0, 0.0, 0.0, 0.0, -0.002002, 0.0, -0.0, 0.0, -1.002002, 1.0))


if __name__ == "__main__":
    unittest.main()
