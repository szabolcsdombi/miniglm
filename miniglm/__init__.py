'''
    Minimalist pythonic matrix, vector, quaternion math.

    Matrices are stored in column-major order.

    This module is using glm.
'''

import os

if os.environ.get('READTHEDOCS') == 'True':
    from .mock import (
        Vec2, Vec3, Vec4, Mat2, Mat3, Mat4, Quat,
        mat4_perspective, mat4_ortho, mat4_look_at,
    )

else:
    from .glm import (
        Vec2, Vec3, Vec4, Mat2, Mat3, Mat4, Quat,
        mat4_perspective, mat4_ortho, mat4_look_at,
    )

__all__ = [
    'Vec2', 'Vec3', 'Vec4', 'Mat2', 'Mat3', 'Mat4', 'Quat',
    'mat4_perspective', 'mat4_ortho', 'mat4_look_at',
]

__version__ = '0.2.3'
