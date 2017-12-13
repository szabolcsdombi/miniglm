import unittest

from miniglm import Vec3Array
from common import MyTestCase


class TestCase(MyTestCase):
    def test_1(self):
        a = Vec3Array((1.0, 2.0, 3.0) * 1000)
        b = Vec3Array((4.0, -4.0, 5.0) * 1000)
        self.assertAlmostEqual2(a + b, (5.0, -2.0, 8.0) * 1000)
        self.assertAlmostEqual2(a - b, (-3.0, 6.0, -2.0) * 1000)
        self.assertAlmostEqual2(a * b, (4.0, -8.0, 15.0) * 1000)
        self.assertAlmostEqual2(a / b, (0.25, -0.5, 0.6) * 1000)

    def test_2(self):
        a = Vec3Array((1.0, 2.0, 3.0) * 1000)
        self.assertAlmostEqual2(a * 2, (2.0, 4.0, 6.0) * 1000)
        self.assertAlmostEqual2(a / 2, (0.5, 1.0, 1.5) * 1000)
        self.assertAlmostEqual2(+a, (1.0, 2.0, 3.0) * 1000)
        self.assertAlmostEqual2(-a, (-1.0, -2.0, -3.0) * 1000)

    def test_3(self):
        a = Vec3Array((1.0, 2.0, 3.0))
        self.assertAlmostEqual2(a.normal, (0.26726123690605164, 0.5345224738121033, 0.8017836809158325))
        self.assertAlmostEqual2(a.length, (3.7416574954986572, ))
        self.assertAlmostEqual2(a.normal.length, (1.0, ))
    
    def test_4(self):
        a = Vec3Array((1.0, 2.0, 3.0) * 1000)
        b = Vec3Array((1.0, 1.0, 1.0) * 1000)
        self.assertAlmostEqual2(a.out(b), (1.0, 1.0, 1.0, 2.0, 2.0, 2.0, 3.0, 3.0, 3.0) * 1000)


if __name__ == '__main__':
    unittest.main()
