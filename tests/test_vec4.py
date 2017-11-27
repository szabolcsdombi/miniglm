import unittest

from miniglm import Vec4
from common import MyTestTest


class TestCase(MyTestTest):
    def test_1(self):
        a = Vec4((1.0, 2.0, 3.0, -4.0))
        b = Vec4((4.0, -4.0, 5.0, -4.0))
        self.assertAlmostEqual2(a + b, (5.0, -2.0, 8.0, -8.0))
        self.assertAlmostEqual2(a - b, (-3.0, 6.0, -2.0, 0.0))
        self.assertAlmostEqual2(a * b, (4.0, -8.0, 15.0, 16.0))
        self.assertAlmostEqual2(a / b, (0.25, -0.5, 0.6, 1.0))

    def test_2(self):
        a = Vec4((1.0, 2.0, 3.0, -4.0))
        self.assertAlmostEqual2(a * 2, (2.0, 4.0, 6.0, -8.0))
        self.assertAlmostEqual2(a / 2, (0.5, 1.0, 1.5, -2.0))
        self.assertAlmostEqual2(+a, (1.0, 2.0, 3.0, -4.0))
        self.assertAlmostEqual2(-a, (-1.0, -2.0, -3.0, 4.0))

    def test_3(self):
        a = Vec4((1.0, 2.0, 3.0, -4.0))
        self.assertAlmostEqual2(a, a.normal * a.length)
        self.assertAlmostEqual2(a.normal, (0.18257418274879456, 0.3651483654975891, 0.547722578048706, -0.7302967309951782))
        self.assertAlmostEqual1(a.length, 5.4772257804870605)
        self.assertAlmostEqual1(a.normal.length, 1.0)


if __name__ == '__main__':
    unittest.main()
