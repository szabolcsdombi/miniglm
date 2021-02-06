import struct

import numpy as np
import pytest

import miniglm


def test_add_vec_vec():
    res = miniglm.add((1.0, 2.0, 3.0), (1.5, 1.8, 1.2))
    np.testing.assert_almost_equal(res, (2.5, 3.8, 4.2))
    assert type(res) is tuple


def test_add_vec_scalar():
    res = miniglm.add((1.0, 2.0, 3.0), 0.5)
    np.testing.assert_almost_equal(res, (1.5, 2.5, 3.5))
    assert type(res) is tuple


def test_sub_vec_vec():
    res = miniglm.sub((5.0, 6.0, 7.0), (1.5, 1.8, 1.2))
    np.testing.assert_almost_equal(res, (3.5, 4.2, 5.8))
    assert type(res) is tuple


def test_sub_vec_scalar():
    res = miniglm.sub((5.0, 6.0, 7.0), 1.5)
    np.testing.assert_almost_equal(res, (3.5, 4.5, 5.5))
    assert type(res) is tuple


def test_mul_vec_vec():
    res = miniglm.mul((5.0, 6.0, 7.0), (1.5, 1.8, 1.2))
    np.testing.assert_almost_equal(res, (7.5, 10.8, 8.4))
    assert type(res) is tuple


def test_mul_vec_scalar():
    res = miniglm.mul((1.0, 2.0, 3.0), 2.0)
    np.testing.assert_almost_equal(res, (2.0, 4.0, 6.0))
    assert type(res) is tuple


def test_cross():
    res = miniglm.cross((2.0, 3.5, 7.1), (0.2, 10.0, 3.3))
    np.testing.assert_almost_equal(res, (-59.45, -5.18, 19.3))
    assert type(res) is tuple


def test_dot_vec():
    res = miniglm.dot((2.0, 3.5, 7.1), (0.2, 10.0, 3.3))
    np.testing.assert_almost_equal(res, 58.83)


def test_dot_quat():
    res = miniglm.dot((2.0, 3.5, 7.1), (0.2, 10.0, 3.3))
    np.testing.assert_almost_equal(res, 58.83)


def test_mix_vec():
    res = miniglm.mix((2.5, 3.4, 4.6), (7.2, 1.1, 3.2), 0.2)
    np.testing.assert_almost_equal(res, (3.44, 2.94, 4.32))
    assert type(res) is tuple


def test_mix_scalar():
    res = miniglm.mix(1.0, 3.0, 0.5)
    np.testing.assert_almost_equal(res, 2.0)


def test_rotation():
    res = miniglm.rotation(miniglm.pi / 3.0, miniglm.normalize((0.48, 0.60, 0.64)))
    expected = (0.24, 0.3, 0.32, 0.8660254037844387)
    np.testing.assert_almost_equal(res, expected)
    assert type(res) is tuple


def test_rotation_x_90_deg():
    res = miniglm.rotation(miniglm.pi / 2.0, (1.0, 0.0, 0.0))
    np.testing.assert_almost_equal(res, (np.sqrt(2.0) / 2.0, 0.0, 0.0, np.sqrt(2.0) / 2.0))


def test_rotation_y_90_deg():
    res = miniglm.rotation(miniglm.pi / 2.0, (0.0, 1.0, 0.0))
    np.testing.assert_almost_equal(res, (0.0, np.sqrt(2.0) / 2.0, 0.0, np.sqrt(2.0) / 2.0))


def test_rotation_z_90_deg():
    res = miniglm.rotation(miniglm.pi / 2.0, (0.0, 0.0, 1.0))
    np.testing.assert_almost_equal(res, (0.0, 0.0, np.sqrt(2.0) / 2.0, np.sqrt(2.0) / 2.0))


def test_normalize_vec():
    res = miniglm.normalize((48.0, 60.0, 64.0))
    expected = (0.48, 0.60, 0.64)
    np.testing.assert_almost_equal(res, expected)
    assert type(res) is tuple


def test_normalize_quat():
    res = miniglm.normalize((2.0, 4.0, 8.0, 4.0))
    expected = (0.2, 0.4, 0.8, 0.4)
    np.testing.assert_almost_equal(res, expected)
    assert type(res) is tuple


def test_normalize_mat():
    mat = (
        0.074, 0.962, -0.259,
        -0.518, 0.259, 0.814,
        0.851, 0.074, 0.518,
    )
    res = miniglm.normalize(mat)
    np.testing.assert_almost_equal(miniglm.det(res), 1.0)
    np.testing.assert_almost_equal(miniglm.cross(res[0:3], res[3:6]), res[6:9])
    np.testing.assert_almost_equal(miniglm.dot(res[0:3], res[3:6]), 0.0)
    np.testing.assert_almost_equal(miniglm.dot(res[3:6], res[6:9]), 0.0)
    np.testing.assert_almost_equal(miniglm.dot(res[0:3], res[6:9]), 0.0)
    assert type(res) is tuple


def test_cast():
    quat = (0.2, 0.4, 0.8, 0.4)
    mat = (-0.6, 0.8, 0.0, -0.48, -0.36, 0.8, 0.64, 0.48, 0.6)
    np.testing.assert_almost_equal(miniglm.cast(quat), mat)
    np.testing.assert_almost_equal(miniglm.cast(mat), quat)
    np.testing.assert_almost_equal(miniglm.cast(miniglm.cast(quat)), quat)
    np.testing.assert_almost_equal(miniglm.cast(miniglm.cast(mat)), mat)


def test_swizzle_vec():
    res = miniglm.swizzle((1.0, 2.0, 3.0), 'yxz')
    np.testing.assert_almost_equal(res, (2.0, 1.0, 3.0))


def test_swizzle_quat():
    res = miniglm.swizzle((0.1, 0.7, 0.5, 0.5), 'wxyz')
    np.testing.assert_almost_equal(res, (0.5, 0.1, 0.7, 0.5))


def test_pack_scalar():
    assert miniglm.pack(1.75) == struct.pack('f', 1.75)


def test_pack_vec():
    vec = (1.0, 2.0, 3.0)
    assert miniglm.pack(vec) == struct.pack('fff', *vec)


def test_pack_quat():
    quat = (0.1, 0.7, 0.5, 0.5)
    assert miniglm.pack(quat) == struct.pack('ffff', *quat)


def test_pack_mat():
    mat = (1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0)
    assert miniglm.pack(mat) == struct.pack('fffffffff', *mat)
