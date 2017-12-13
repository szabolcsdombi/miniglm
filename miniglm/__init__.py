'''
    Minimalist pythonic matrix, vector, quaternion math.

    Matrices are stored in column-major order.

    This module is using glm.
'''

import os
import sys

if os.environ.get('READTHEDOCS') == 'True' or sys.argv[0] == 'completion.py':
    from .mock import (
        Vec2, Vec3, Vec4, Mat2, Mat3, Mat4, Quat,
        mat4_perspective, mat4_ortho, mat4_look_at,
        radians, degrees,
    )

else:
    from .glm import (
        Vec2, Vec3, Vec4, Mat2, Mat3, Mat4, Quat,
        Vec2Array, Vec3Array, Vec4Array, Mat2Array, Mat3Array, Mat4Array, QuatArray, FloatArray,
        mat4_perspective, mat4_ortho, mat4_look_at,
    )


    def radians(deg):
        return deg / 57.2957795131


    def degrees(rad):
        return rad * 57.2957795131


__all__ = [
    'Vec2', 'Vec3', 'Vec4', 'Mat2', 'Mat3', 'Mat4', 'Quat',
    'Vec2Array', 'Vec3Array', 'Vec4Array', 'Mat2Array', 'Mat3Array', 'Mat4Array', 'QuatArray', 'FloatArray',
    'mat4_perspective', 'mat4_ortho', 'mat4_look_at',
    'radians', 'degrees',
]

__version__ = '0.2.5'
