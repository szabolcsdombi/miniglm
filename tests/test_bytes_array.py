import unittest
import struct

from miniglm import Vec2Array, Vec3Array, Vec4Array, Mat2Array, Mat3Array, Mat4Array, QuatArray, FloatArray
from common import MyTestCase


class TestCase(MyTestCase):
    def test_vec2_array_bytes(self):
        a = Vec2Array((1.0, 2.0) * 2)
        self.assertAlmostEqual2(a, struct.unpack('f' * len(a), bytes(a)))
    
    def test_vec3_array_bytes(self):
        a = Vec3Array((1.0, 2.0, 3.0) * 2)
        self.assertAlmostEqual2(a, struct.unpack('f' * len(a), bytes(a)))

    def test_vec4_array_bytes(self):
        a = Vec4Array((1.0, 2.0, 3.0, 4.0) * 2)
        self.assertAlmostEqual2(a, struct.unpack('f' * len(a), bytes(a)))

    def test_mat2_array_bytes(self):
        a = Mat2Array((1, 2, 3, 4) * 2)
        self.assertAlmostEqual2(a, struct.unpack('f' * len(a), bytes(a)))
    
    def test_mat3_array_bytes(self):
        a = Mat3Array((1, 2, 3, 4, 5, 6, 7, 8, 9) * 2)
        self.assertAlmostEqual2(a, struct.unpack('f' * len(a), bytes(a)))

    def test_mat4_array_bytes(self):
        a = Mat4Array((1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16) * 2)
        self.assertAlmostEqual2(a, struct.unpack('f' * len(a), bytes(a)))

    def test_quat_array_bytes(self):
        a = QuatArray((0, 0, 0, 1 * 2))
        self.assertAlmostEqual2(a, struct.unpack('f' * len(a), bytes(a)))
    
    def test_float_array_bytes(self):
        a = FloatArray((1, 2, 3) * 1000)
        self.assertAlmostEqual2(a, struct.unpack('f' * len(a), bytes(a)))
if __name__ == '__main__':
    unittest.main()
