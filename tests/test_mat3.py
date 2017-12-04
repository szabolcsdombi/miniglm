import unittest
from math import inf
from miniglm import Mat3, Vec3
from common import MyTestCase


class TestCase(MyTestCase):
    def test_1(self):
        a = Mat3((4.0, 4.0, 4.0, 2.0, 2.0, 2.0, 1.0, 1.0, 1.0))
        b = Mat3((2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0))
        c = Vec3((2.0, 2.0, 2.0))
        self.assertAlmostEqual2(a + b, (6.0, 6.0, 6.0, 4.0, 4.0, 4.0, 3.0, 3.0, 3.0))
        self.assertAlmostEqual2(a - b, (2.0, 2.0, 2.0, 0.0, 0.0, 0.0, -1.0, -1.0, -1.0))
        self.assertAlmostEqual2(a * b, (14.0, 14.0, 14.0, 14.0, 14.0, 14.0, 14.0, 14.0, 14.0))
        self.assertAlmostEqual2(a * c, (14.0, 14.0, 14.0))

    def test_2(self):
        a = Mat3((4.0, 4.0, 4.0, 2.0, 2.0, 2.0, 1.0, 1.0, 1.0))
        self.assertAlmostEqual2(a * 2, (8.0, 8.0, 8.0, 4.0, 4.0, 4.0, 2.0, 2.0, 2.0))
        self.assertAlmostEqual2(a / 2, (2.0, 2.0, 2.0, 1.0, 1.0, 1.0, .5, .5, .5))
        self.assertAlmostEqual2(-a, (-4.0, -4.0, -4.0, -2.0, -2.0, -2.0, -1.0, -1.0, -1.0))
        self.assertAlmostEqual2(+a, (4.0, 4.0, 4.0, 2.0, 2.0, 2.0, 1.0, 1.0, 1.0))


    def test_3(self):
        a = Mat3((1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0))
        b = Mat3((-10.0, -2.0, -7.0, 6.0, -8.0, 5.0, 5.0, -7.0, 3.0))
        self.assertAlmostEqual2(a.trans, (1.0, 4.0, 7.0, 2.0, 5.0, 8.0, 3.0, 6.0, 9.0))
        self.assertAlmostEqual1(a.det, 0)
        self.assertAlmostEqual1(b.det, -110)
        self.assertAlmostEqual2(b.inv, (-0.1, -.5, 3 / 5, -7 / 110, - 1 / 22, -4 / 55, 1 / 55, 8 / 11, -46 / 55))
        self.assertAlmostEqual2(a.tup, [1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0])
        self.assertAlmostEqual2(a.row(0), (1.0, 4.0, 7.0))
        self.assertAlmostEqual2(a.col(0), (1.0, 2.0, 3.0))

if __name__ == "__main__":
    unittest.main()