import unittest
from math import inf
from miniglm import Mat4Array, Vec4Array
from common import MyTestCase


class TestCase(MyTestCase):
    def test_1(self):
        a = Mat4Array((4.0, 4.0, 4.0, 4.0, 2.0, 2.0, 2.0, 2.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0) * 100)
        b = Mat4Array((2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0) * 100)
        c = Vec4Array((2.0, 2.0, 2.0, 2.0) * 100)
        self.assertAlmostEqual2(a + b, (6.0, 6.0, 6.0, 6.0, 4.0, 4.0, 4.0, 4.0, 3.0, 3.0, 3.0, 3.0, 2.0, 2.0, 2.0, 2.0) * 100)
        self.assertAlmostEqual2(a - b, (2.0, 2.0, 2.0, 2.0, 0.0, 0.0, 0.0, 0.0, -1.0, -1.0, -1.0, -1.0, -2.0, -2.0, -2.0, -2.0) * 100)
        self.assertAlmostEqual2(a * b, (14.0, 14.0, 14.0, 14.0, 14.0, 14.0, 14.0, 14.0, 14.0, 14.0, 14.0, 14.0, 14.0, 14.0, 14.0, 14.0) * 100)
        self.assertAlmostEqual2(a * c, (14.0, 14.0, 14.0, 14.0) * 100)

    def test_2(self):
        a = Mat4Array((4.0, 4.0, 4.0, 4.0, 2.0, 2.0, 2.0, 2.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0) * 100)
        self.assertAlmostEqual2(a * 2, (8.0, 8.0, 8.0, 8.0, 4.0, 4.0, 4.0, 4.0, 2.0, 2.0, 2.0, 2.0, 0.0, 0.0, 0.0, 0.0) * 100)
        self.assertAlmostEqual2(a / 2, (2.0, 2.0, 2.0, 2.0, 1.0, 1.0, 1.0, 1.0, .5, .5, .5, .5, 0.0, 0.0, 0.0, 0.0) * 100)
        self.assertAlmostEqual2(-a, (-4.0, -4.0, -4.0, -4.0, -2.0, -2.0, -2.0, -2.0, -1.0, -1.0, -1.0, -1.0, -0.0, -0.0, -0.0, -0.0) * 100)
        self.assertAlmostEqual2(+a, (4.0, 4.0, 4.0, 4.0, 2.0, 2.0, 2.0, 2.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0) * 100)

    def test_3(self):
        a = Mat4Array((1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0) * 100)
        b = Mat4Array((9.0, -6.0, -2.0, 9.0, 1.0, 2.0, 2.0, 4.0, 3.0, 4.0, 7.0, -8.0, -10.0, -1.0, 1.0, -2.0) * 100)
        self.assertAlmostEqual2(a.trans, (1.0, 5.0, 9.0, 13.0, 2.0, 6.0, 10.0, 14.0, 3.0, 7.0, 11.0, 15.0, 4.0, 8.0, 12.0, 16.0) * 100)
        self.assertAlmostEqual2(a.det, (0.0, ) * 100)
        self.assertAlmostEqual2(b.det, (3265.0, ) * 100)
        self.assertAlmostEqual2(b.inv, (64 / 3265, -103 / 3265, 84 / 3265, -254 / 3265, -458 / 3265, 431 / 3265, -193 / 3265, -427 / 3265, 304 / 3265, 327 / 3265, 399 / 3265, 426 / 3265, 61 / 3265, 463 / 3265, -124 / 3265, 64 / 3265) * 100)
        self.assertAlmostEqual2(a.tup, [1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0] * 100)
        self.assertAlmostEqual2(a.row(0), (1.0, 5.0, 9.0, 13.0) * 100)
        self.assertAlmostEqual2(a.col(0), (1.0, 2.0, 3.0, 4.0) * 100)


if __name__ == "__main__":
    unittest.main()