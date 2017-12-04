import unittest

from math import cos, sin
from miniglm import mat4_look_at, mat4_ortho, mat4_perspective
from common import MyTestCase


class TestCase(MyTestCase):
    def test_mat4_perspective(self):
        projection = mat4_perspective(90, 1.0, 1.0, 10.0)
        self.assertAlmostEqual2(projection, (0.617369, 0.0, 0.0, 0.0, 0.0, 0.617369, 0.0, 0.0, 0.0, 0.0, -1.222222, -1.0, 0.0, 0.0, -2.222222, 0.0))

        projection = mat4_perspective(90, 2.0, 1.0, 10.0)
        self.assertAlmostEqual2(projection, (0.308684, 0.0, 0.0, 0.0, 0.0, 0.617369, 0.0, 0.0, 0.0, 0.0, -1.222222, -1.0, 0.0, 0.0, -2.222222, 0.0))

        projection = mat4_perspective(60, 1.5, 1.0, 10.0)
        self.assertAlmostEqual2(projection, (-0.104079, 0.0, 0.0, 0.0, 0.0, -0.156119, 0.0, 0.0, 0.0, 0.0, -1.222222, -1.0, 0.0, 0.0, -2.222222, 0.0))

        projection = mat4_perspective(60, 1.5, 0.1, 100.0)
        self.assertAlmostEqual2(projection, (-0.104079, 0.0, 0.0, 0.0, 0.0, -0.156119, 0.0, 0.0, 0.0, 0.0, -1.002002, -1.0, 0.0, 0.0, -0.200200, 0.0))

    def test_mat4_look_at(self):
        a = mat4_look_at(
            (cos(0.5) * 5.0, sin(0.5) * 5.0, 2.0),
            (0.0, 0.0, 0.5),
            (0.0, 0.0, 1.0)
        )
        self.assertAlmostEqual2(a, (-0.4794255495071411, -0.25217148661613464, 0.8405716419219971, 0.0, 0.8775825500488281, -0.1377619206905365, 0.45920637249946594, 0.0, 0.0, 0.9578262567520142, 0.2873478829860687, 0.0, 2.384185791015625e-07, -0.4789130687713623, -5.363826751708984, 1.0))

    def test_mat4_ortho(self):
        a = mat4_ortho(-1.0, 1.0, 1.0, -1.0, 1.0, 1000.0)
        self.assertAlmostEqual2(a, (1.0, 0.0, 0.0, 0.0, 0.0, -1.0, 0.0, 0.0, 0.0, 0.0, -0.002002002002, 0.0, -0.0, 0.0, -1.002002002, 1.0))


if __name__ == "__main__":
    unittest.main()
