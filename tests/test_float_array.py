import unittest

from miniglm import FloatArray, Vec2Array, Vec3Array, Vec4Array, Mat2Array, Mat3Array, Mat4Array, QuatArray
from common import MyTestCase


class TestCase(MyTestCase):
    def test_1(self):
        a = FloatArray((1, 2, 3, 4, 5) * 1000)
        b = FloatArray((5, 4, 3, 2, 1) * 1000)
        self.assertAlmostEqual2(a + b, (6, 6, 6, 6, 6) * 1000)
        self.assertAlmostEqual2(a - b, (-4, -2, 0, 2, 4) * 1000)
        self.assertAlmostEqual2(a * b, (5, 8, 9, 8, 5) * 1000)
        self.assertAlmostEqual2(a / b, (1/5, 1/2, 1, 2, 5) * 1000)

    def test_2(self):
        a = FloatArray((1, 2, 3, 4, 5) * 1000)
        self.assertAlmostEqual2(a + 1, (2, 3, 4, 5, 6) * 1000)
        self.assertAlmostEqual2(a - 1, (0, 1, 2, 3, 4) * 1000)
        self.assertAlmostEqual2(a * 2, (2, 4, 6, 8, 10) * 1000)
        self.assertAlmostEqual2(a / 2, (1/2, 2/2, 3/2, 4/2, 5/2) * 1000)
    
    def test_3(self):
        a = FloatArray((1, 2, 3, 4, 5) * 1000)
        self.assertAlmostEqual2(-a, (-1, -2, -3, -4, -5) * 1000)
        self.assertAlmostEqual2(+a, (+1, +2, +3, +4, +5) * 1000)

    def test_4(self):
        a = FloatArray((1, 2, 3) * 500)
        b = Vec2Array((1, 1, 2, 2, 3, 3) * 500)
        self.assertAlmostEqual2(a * b, (1, 1, 4, 4, 9, 9) * 500)
        self.assertAlmostEqual2(a / b, (1, 1, 1, 1, 1, 1) * 500)
    
    def test_5(self):
        a = FloatArray((1, 2, 3) * 500)
        b = Vec3Array((1, 1, 1, 2, 2, 2, 3, 3, 3) * 500)
        self.assertAlmostEqual2(a * b, (1, 1, 1, 4, 4, 4, 9, 9, 9) * 500)
        self.assertAlmostEqual2(a / b, (1, 1, 1, 1, 1, 1, 1, 1, 1) * 500)

    def test_6(self):
        a = FloatArray((1, 2, 3) * 500)
        b = Vec4Array((1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3) * 500)
        self.assertAlmostEqual2(a * b, (1, 1, 1, 1, 4, 4, 4, 4, 9, 9, 9, 9) * 500)
        self.assertAlmostEqual2(a / b, (1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1) * 500)

    def test_7(self):
        a = FloatArray((1, 2, 3) * 500)
        b = Mat2Array((1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3) * 500)
        self.assertAlmostEqual2(a * b, (1, 1, 1, 1, 4, 4, 4, 4, 9, 9, 9, 9) * 500)
        self.assertAlmostEqual2(a / b, (1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1) * 500)
    
    def test_8(self):
        a = FloatArray((1, 2, 3) * 500)
        b = Mat3Array((1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3) * 500)
        self.assertAlmostEqual2(a * b, (1, 1, 1, 1, 1, 1, 1, 1, 1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 9, 9, 9, 9, 9, 9, 9, 9, 9) * 500)
        self.assertAlmostEqual2(a / b, (1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1) * 500)

    def test_9(self):
        a = FloatArray((1, 2, 3) * 500)
        b = Mat4Array((1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3) * 500)
        self.assertAlmostEqual2(a * b, (1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9) * 500)
        self.assertAlmostEqual2(a / b, (1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1) * 500)
    
    def test_10(self):
        a = FloatArray((1, 2, 3) * 500)
        b = QuatArray((0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1) * 500)
        self.assertAlmostEqual2(a * b, (0, 0, 0, 1, 0, 0, 0, 2, 0, 0, 0, 3) * 500)

if __name__ == "__main__":
    unittest.main()
