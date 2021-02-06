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


def test_mix_vec_vec():
    res = miniglm.mix((2.5, 3.4, 4.6), (7.2, 1.1, 3.2), 0.2)
    np.testing.assert_almost_equal(res, (3.44, 2.94, 4.32))
    assert type(res) is tuple


def test_rotation():
    res = miniglm.rotation(0.75, miniglm.normalize((1.0, 2.0, 3.0)))
    expected = (0.09789045100194166, 0.19578090200388332, 0.293671353005825, 0.9305076219123143)
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
    res = miniglm.normalize((2.0, 3.0, 4.0))
    expected = (0.3713906763541037, 0.5570860145311556, 0.7427813527082074)
    np.testing.assert_almost_equal(res, expected)
    assert type(res) is tuple


def test_normalize_quat():
    res = miniglm.normalize((2.0, 3.0, 4.0, 5.0))
    expected = (0.2721655269759087, 0.408248290463863, 0.5443310539518174, 0.6804138174397717)
    np.testing.assert_almost_equal(res, expected)
    assert type(res) is tuple


def test_cast():
    quat = (0.2721655269759087, 0.408248290463863, 0.5443310539518174, 0.6804138174397717)
    mat = (
        0.07407407407407418, 0.9629629629629629, -0.2592592592592593,
        -0.5185185185185185, 0.2592592592592593, 0.8148148148148148,
        0.8518518518518519, 0.07407407407407407, 0.5185185185185186,
    )
    np.testing.assert_almost_equal(miniglm.cast(quat), mat)
    np.testing.assert_almost_equal(miniglm.cast(mat), quat)
    np.testing.assert_almost_equal(miniglm.cast(miniglm.cast(quat)), quat)
    np.testing.assert_almost_equal(miniglm.cast(miniglm.cast(mat)), mat)


def test_swizzle_vec():
    res = miniglm.swizzle((1.0, 2.0, 3.0), 'yxz')
    np.testing.assert_almost_equal(res, (2.0, 1.0, 3.0))


def test_swizzle_quat():
    res = miniglm.swizzle((0.272, 0.408, 0.544, 0.680), 'wxyz')
    np.testing.assert_almost_equal(res, (0.680, 0.272, 0.408, 0.544))


def test_pack_scalar():
    assert miniglm.pack(1.75) == struct.pack('f', 1.75)


def test_pack_vec():
    vec = (1.0, 2.0, 3.0)
    assert miniglm.pack(vec) == struct.pack('fff', *vec)


def test_pack_quat():
    quat = (0.272, 0.408, 0.544, 0.680)
    assert miniglm.pack(quat) == struct.pack('ffff', *quat)


def test_pack_mat():
    mat = (1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0)
    assert miniglm.pack(mat) == struct.pack('fffffffff', *mat)
