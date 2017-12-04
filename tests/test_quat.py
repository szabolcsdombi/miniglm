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
        self.assertAlmostEqual2(a * b, (1.399999976158142, 1.600000023841858, 0.8000000715255737, 0.20000001788139343))

    def test_3(self):
        a = Quat((1.0, 1.0, 1.0, 1.0))
        b = Quat((.5, .2, .1, 1))
        self.assertAlmostEqual1(a.length, 2.0)
        self.assertAlmostEqual2(a.normal, (0.5,  0.5,  0.5,  0.5))
        self.assertAlmostEqual2(a.conj, (-1., -1., -1.,  1.))
        self.assertAlmostEqual2(a.normal.inv, (-0.5, -0.5, -0.5,  0.5))
        self.assertAlmostEqual2(a.tup, [1.0, 1.0, 1.0, 1.0])
        self.assertAlmostEqual1(a.dot(b), 1.7999999999999998)
        self.assertAlmostEqual2(a.cross(b), ( 1.4,  1.6,  0.8,  0.2))

    def test_4(self):
        self.skipTest('TODO: Fix lerp and slerp')
        a = Quat((1.0, 1.0, 1.0, 1.0))
        b = Quat((.5, .2, .1, 1))
        self.assertAlmostEqual2(Quat.slerp(a, b, 2), (0.43852901,  0.1754116 ,  0.0877058 ,  0.87705802))
        self.assertAlmostEqual2(Quat.lerp(a, b, 2), (0.43852901,  0.1754116 ,  0.0877058 ,  0.87705802))


if __name__ == "__main__":
    unittest.main()