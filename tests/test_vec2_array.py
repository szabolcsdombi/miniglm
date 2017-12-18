import unittest

from miniglm import Vec2Array
from common import MyTestCase


class TestCase(MyTestCase):
    def test_1(self):
        a = Vec2Array((1.0, 2.0) * 1000)
        b = Vec2Array((4.0, -4.0) * 1000)
        self.assertAlmostEqual2(a + b, (5.0, -2.0) * 1000)
        self.assertAlmostEqual2(a - b, (-3.0, 6.0) * 1000)
        self.assertAlmostEqual2(a * b, (4.0, -8.0) * 1000)
        self.assertAlmostEqual2(a / b, (0.25, -0.5) * 1000)

    def test_2(self):
        a = Vec2Array((1.0, 2.0) * 1000)
        self.assertAlmostEqual2(a * 2, (2.0, 4.0) * 1000)
        self.assertAlmostEqual2(a / 2, (0.5, 1.0) * 1000)
        self.assertAlmostEqual2(+a, (1.0, 2.0) * 1000)
        self.assertAlmostEqual2(-a, (-1.0, -2.0) * 1000)

    def test_3(self):
        a = Vec2Array((1.0, 2.0) * 1000)
        self.assertAlmostEqual2(a.normal, (0.4472135901451111, 0.8944271802902222) * 1000)
        self.assertAlmostEqual2(a.length, (2.2360680103302, ) * 1000)
        self.assertAlmostEqual2(a.normal.length, (1.0, ) * 1000)

    def test_4(self):
        a = Vec2Array((1, 2) * 1000)
        b = Vec2Array((1, 1) * 1000)
        self.assertAlmostEqual2(a.out(b), (1.0, 1.0, 2.0, 2.0) * 1000)
 
if __name__ == '__main__':
    unittest.main()
