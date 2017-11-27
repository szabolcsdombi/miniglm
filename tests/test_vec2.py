import unittest

from miniglm import Vec2
from common import MyTestCase


class TestCase(MyTestCase):
    def test_1(self):
        a = Vec2((1.0, 2.0))
        b = Vec2((4.0, -4.0))
        self.assertAlmostEqual2(a + b, (5.0, -2.0))
        self.assertAlmostEqual2(a - b, (-3.0, 6.0))
        self.assertAlmostEqual2(a * b, (4.0, -8.0))
        self.assertAlmostEqual2(a / b, (0.25, -0.5))

    def test_2(self):
        a = Vec2((1.0, 2.0))
        self.assertAlmostEqual2(a * 2, (2.0, 4.0))
        self.assertAlmostEqual2(a / 2, (0.5, 1.0))
        self.assertAlmostEqual2(+a, (1.0, 2.0))
        self.assertAlmostEqual2(-a, (-1.0, -2.0))

    def test_3(self):
        a = Vec2((1.0, 2.0))
        self.assertAlmostEqual2(a, a.normal * a.length)
        self.assertAlmostEqual2(a.normal, (0.4472135901451111, 0.8944271802902222))
        self.assertAlmostEqual1(a.length, 2.2360680103302)
        self.assertAlmostEqual1(a.normal.length, 1.0)


if __name__ == '__main__':
    unittest.main()
