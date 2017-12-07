import math
import unittest

from miniglm import QuatArray
from common import MyTestCase


class TestCase(MyTestCase):
    def test_1(self):
        a = QuatArray((1.0, 1.0, 1.0, 1.0) * 1000)
        self.assertAlmostEqual2(a * 2, (2.0, 2.0, 2.0, 2.0) * 1000)
        self.assertAlmostEqual2(a / 2, (0.5, 0.5, 0.5, 0.5) * 1000)

    def test_2(self):
        a = QuatArray((1.0, 1.0, 1.0, 1.0) * 1000)
        b = QuatArray((0.5, 0.2, 0.1, 1.0) * 1000)
        self.assertAlmostEqual2(a * b, (1.4, 1.6, 0.8, 0.2) * 1000)

    def test_3(self):
        a = QuatArray((1.0, 1.0, 1.0, 1.0) * 1000)
        b = QuatArray((.5, .2, .1, 1) * 1000)
        self.assertAlmostEqual1(a.length, (2.0, ) * 1000)
        self.assertAlmostEqual2(a.normal, (0.5, 0.5, 0.5, 0.5) * 1000)
        self.assertAlmostEqual2(a.conj, (-1.0, -1.0, -1.0, 1.0) * 1000)
        self.assertAlmostEqual2(a.normal.inv, (-0.5, -0.5, -0.5, 0.5) * 1000)
        self.assertAlmostEqual2(a.tup, (1.0, 1.0, 1.0, 1.0) * 1000)
        self.assertAlmostEqual2(a.dot(b), (1.8, ) * 1000)
        self.assertAlmostEqual2(a.cross(b), (1.4, 1.6, 0.8, 0.2) * 1000)

    def test_quatArrayernion_slerp(self):
        identity = QuatArray((0.0, 0.0, 0.0, 1.0) * 1000)
        y90rot = QuatArray((0.0, 0.7071067811865476, 0.0, 0.7071067811865476) * 1000)
        y180rot = QuatArray((0.0, 1.0, 0.0, 0.0) * 1000)

        result = identity.slerp(y90rot, 0.0)
        self.assertAlmostEqual2(result, identity)

        result = identity.slerp(y90rot, 1.0)
        self.assertAlmostEqual2(result, y90rot)

        y45rot1 = identity.slerp(y90rot, 0.5)
        y45rot2 = y90rot.slerp(identity, 0.5)
        self.assertAlmostEqual2(y45rot1, y45rot2)

        y45rot3 = identity.slerp(y90rot, 0.5)
        y45angle3 = y45rot3.angle
        self.assertAlmostEqual2(y45angle3, (math.pi / 4, ) * 1000)

        y90rot3 = y90rot.slerp(y90rot, 0.5)
        self.assertAlmostEqual2(y90rot3, y90rot)

        xz90rot = identity.slerp(-y90rot, 0.5)
        xz90rot_angle = xz90rot.angle
        self.assertAlmostEqual2(xz90rot_angle, (math.pi / 4, ) * 1000)


if __name__ == "__main__":
    unittest.main()
