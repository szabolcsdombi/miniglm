import unittest

from miniglm import Mat2, Vec2
from common import MyTestCase


class TestCase(MyTestCase):
    def test_1(self):
        a = Mat2((4.0, 4.0, 2.0, 2.0))
        b = Mat2((2.0, 2.0, 2.0, 2.0))
        c = Vec2((2.0, 2.0))
        self.assertAlmostEqual2(a + b, (6.0, 6.0, 4.0, 4.0))
        self.assertAlmostEqual2(a - b, (2.0, 2.0, 0.0, 0.0))
        self.assertAlmostEqual2(a * b, (12.0, 12.0, 12.0, 12.0))
        self.assertAlmostEqual2(a * c, (12.0, 12.0))

    def test_2(self):
        a = Mat2((4.0, 4.0, 2.0, 2.0))
        self.assertAlmostEqual2(a * 2, (8.0, 8.0, 4.0, 4.0))
        self.assertAlmostEqual2(a / 2, (2.0, 2.0, 1.0, 1.0))
        self.assertAlmostEqual2(-a, (-4.0, -4.0, -2.0, -2.0))
        self.assertAlmostEqual2(+a, (+4.0, +4.0, +2.0, +2.0))


    def test_3(self):
        a = Mat2((1.0, 2.0, 3.0, 4.0))
        self.assertAlmostEqual2(a.trans, (1.0, 3.0, 2.0, 4.0))
        self.assertAlmostEqual1(a.det, -2.0)
        self.assertAlmostEqual2(a.inv, (-2.0, 1.0, 1.5, -0.5))
        self.assertAlmostEqual2(a.tup, [1.0, 2.0, 3.0, 4.0])
        self.assertAlmostEqual2(a.row(0), (1.0, 3.0))
        self.assertAlmostEqual2(a.col(0), (1.0, 2.0))

if __name__ == "__main__":
    unittest.main()