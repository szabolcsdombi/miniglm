import unittest

from miniglm import Vec3
from common import MyTestCase


class TestCase(MyTestCase):
    def test_1(self):
        a = Vec3((1.0, 2.0, 3.0))
        b = Vec3((4.0, -4.0, 5.0))
        self.assertAlmostEqual2(a + b, (5.0, -2.0, 8.0))
        self.assertAlmostEqual2(a - b, (-3.0, 6.0, -2.0))
        self.assertAlmostEqual2(a * b, (4.0, -8.0, 15.0))
        self.assertAlmostEqual2(a / b, (0.25, -0.5, 0.6))

    def test_2(self):
        a = Vec3((1.0, 2.0, 3.0))
        self.assertAlmostEqual2(a * 2, (2.0, 4.0, 6.0))
        self.assertAlmostEqual2(a / 2, (0.5, 1.0, 1.5))
        self.assertAlmostEqual2(+a, (1.0, 2.0, 3.0))
        self.assertAlmostEqual2(-a, (-1.0, -2.0, -3.0))

    def test_3(self):
        a = Vec3((1.0, 2.0, 3.0))
        self.assertAlmostEqual2(a, a.normal * a.length)
        self.assertAlmostEqual2(a.normal, (0.26726123690605164, 0.5345224738121033, 0.8017836809158325))
        self.assertAlmostEqual1(a.length, 3.7416574954986572)
        self.assertAlmostEqual1(a.normal.length, 1.0)


if __name__ == '__main__':
    unittest.main()
