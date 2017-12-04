import math
import unittest

from miniglm import Quat
from common import MyTestCase

class TestCase(MyTestCase):
    def test_1(self):
        a = Quat((1.0, 1.0, 1.0, 1.0))
        self.assertAlmostEqual2(a * 2, (2.0, 2.0, 2.0, 2.0))
        self.assertAlmostEqual2(a / 2, (0.5, 0.5, 0.5, 0.5))

    def test_2(self):
        a = Quat((1.0, 1.0, 1.0, 1.0))
        b = Quat((0.5, 0.2, 0.1, 1.0))
        self.assertAlmostEqual2(a * b, (1.4, 1.6, 0.8, 0.2))

    def test_3(self):
        a = Quat((1.0, 1.0, 1.0, 1.0))
        b = Quat((.5, .2, .1, 1))
        self.assertAlmostEqual1(a.length, 2.0)
        self.assertAlmostEqual2(a.normal, (0.5, 0.5, 0.5, 0.5))
        self.assertAlmostEqual2(a.conj, (-1.0, -1.0, -1.0, 1.0))
        self.assertAlmostEqual2(a.normal.inv, (-0.5, -0.5, -0.5, 0.5))
        self.assertAlmostEqual2(a.tup, (1.0, 1.0, 1.0, 1.0))
        self.assertAlmostEqual1(a.dot(b), 1.8)
        self.assertAlmostEqual2(a.cross(b), (1.4, 1.6, 0.8, 0.2))

    def test_quaternion_slerp(self):
        identity = Quat((0.0, 0.0, 0.0, 1.0))
        y90rot = Quat((0.0, 0.7071067811865476, 0.0, 0.7071067811865476))
        y180rot = Quat((0.0, 1.0, 0.0, 0.0))

        result = identity.slerp(y90rot, 0.0)
        self.assertAlmostEqual2(result, identity)

        result = identity.slerp(y90rot, 1.0)
        self.assertAlmostEqual2(result, y90rot)

        y45rot1 = identity.slerp(y90rot, 0.5)
        y45rot2 = y90rot.slerp(identity, 0.5)
        self.assertAlmostEqual2(y45rot1, y45rot2)

        y45rot3 = identity.slerp(y90rot, 0.5)
        y45angle3 = y45rot3.angle
        self.assertAlmostEqual1(y45angle3, math.pi / 4)

        y90rot3 = y90rot.slerp(y90rot, 0.5)
        self.assertAlmostEqual2(y90rot3, y90rot)

        xz90rot = identity.slerp(-y90rot, 0.5)
        xz90rot_angle = xz90rot.angle
        self.assertAlmostEqual1(xz90rot_angle, math.pi / 4)


if __name__ == "__main__":
    unittest.main()
