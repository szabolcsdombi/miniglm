import unittest
import struct

from miniglm import Vec2, Vec3, Vec4, Mat2, Mat3, Mat4, Quat
from common import MyTestCase


class TestCase(MyTestCase):
    def test_vec2_bytes_size(self):
        a = Vec2((0.0, 0.0))
        self.assertEqual(len(bytes(a)), 2 * 4)

    def test_vec2_bytes(self):
        a = Vec2((1.0, 2.0))
        self.assertAlmostEqual2(a, struct.unpack('ff', bytes(a)))

    def test_vec3_bytes_size(self):
        a = Vec3((0.0, 0.0, 0.0))
        self.assertEqual(len(bytes(a)), 3 * 4)
    
    def test_vec3_bytes(self):
        a = Vec3((1.0, 2.0, 3.0))
        self.assertAlmostEqual2(a, struct.unpack('fff', bytes(a)))

    def test_vec4_bytes_size(self):
        a = Vec4((0.0, 0.0, 0.0, 0.0))
        self.assertEqual(len(bytes(a)), 4 * 4)

    def test_vec4_bytes(self):
        a = Vec4((1.0, 2.0, 3.0, 4.0))
        self.assertAlmostEqual2(a, struct.unpack('ffff', bytes(a)))

    def test_mat2_bytes_size(self):
        a = Mat2((0.0, 0.0, 0.0, 0.0))
        self.assertEqual(len(bytes(a)), 4 * 4)

    def test_mat2_bytes(self):
        a = Mat2((1, 2, 3, 4))
        self.assertAlmostEqual2(a, struct.unpack('ffff', bytes(a)))

    def test_mat3_bytes_size(self):
        a = Mat3((0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0))
        self.assertEqual(len(bytes(a)), 9 * 4)
    
    def test_mat3_bytes(self):
        a = Mat3((1, 2, 3, 4, 5, 6, 7, 8, 9))
        self.assertAlmostEqual2(a, struct.unpack('fffffffff', bytes(a)))

    def test_mat4_bytes_size(self):
        a = Mat4((0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0))
        self.assertEqual(len(bytes(a)), 16 * 4)
    
    def test_mat4_bytes(self):
        a = Mat4((1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16))
        self.assertAlmostEqual2(a, struct.unpack('ffffffffffffffff', bytes(a)))

    def test_quat_bytes_size(self):
        a = Quat((0.0, 0.0, 0.0, 0.0))
        self.assertEqual(len(bytes(a)), 4 * 4)

    def test_quat_bytes(self):
        a = Quat((0, 0, 0, 1))
        self.assertAlmostEqual2(a, struct.unpack('ffff', bytes(a)))
if __name__ == '__main__':
    unittest.main()
