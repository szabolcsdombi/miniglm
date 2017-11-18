import unittest
import math

from miniglm import Vec2, Vec3, Vec4, Mat2, Mat3, Mat4, Quat
from common import MyTestTest


class TestCase(MyTestTest):
    def test_vec2_bytes_size(self):
        a = Vec2((0.0, 0.0))
        self.assertEqual(len(bytes(a)), 2 * 4)

    def test_vec3_bytes_size(self):
        a = Vec3((0.0, 0.0, 0.0))
        self.assertEqual(len(bytes(a)), 3 * 4)

    def test_vec4_bytes_size(self):
        a = Vec4((0.0, 0.0, 0.0, 0.0))
        self.assertEqual(len(bytes(a)), 4 * 4)

    def test_mat2_bytes_size(self):
        a = Mat2((0.0, 0.0, 0.0, 0.0))
        self.assertEqual(len(bytes(a)), 4 * 4)

    def test_mat3_bytes_size(self):
        a = Mat3((0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0))
        self.assertEqual(len(bytes(a)), 9 * 4)

    def test_mat4_bytes_size(self):
        a = Mat4((0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0))
        self.assertEqual(len(bytes(a)), 16 * 4)

    def test_quat_bytes_size(self):
        a = Quat((0.0, 0.0, 0.0, 0.0))
        self.assertEqual(len(bytes(a)), 4 * 4)


if __name__ == '__main__':
    unittest.main()
