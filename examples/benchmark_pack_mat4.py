import struct
import time

from miniglm import Mat4
import numpy as np


def measure(func, *args):
    print('Running %s %r - ' % (func.__name__, args), end='')
    start = time.clock()
    func(*args)
    elapsed = time.clock() - start
    print(elapsed, 'seconds')


def struct_pack1(n):
    m = (
        1.0, 0.0, 0.0, 0.0,
        0.0, 1.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 1.0,
    )
    for i in range(n):
        struct.pack('16f', *m)


def struct_pack2(n):
    s = struct.Struct('16f')
    m = (
        1.0, 0.0, 0.0, 0.0,
        0.0, 1.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 1.0,
    )
    for i in range(n):
        s.pack(*m)


def mat_to_bytes(n):
    v = Mat4((
        1.0, 0.0, 0.0, 0.0,
        0.0, 1.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 1.0,
    ))
    for i in range(n):
        bytes(v)


def mat_data(n):
    v = Mat4((
        1.0, 0.0, 0.0, 0.0,
        0.0, 1.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 1.0,
    ))
    for i in range(n):
        v.data


def np_array_tobytes(n):
    a = np.array((
        1.0, 0.0, 0.0, 0.0,
        0.0, 1.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 1.0,
    ), dtype='f4')
    for i in range(n):
        a.tobytes()


measure(struct_pack1, 10000000)
measure(struct_pack2, 10000000)
measure(mat_to_bytes, 10000000)
measure(mat_data, 10000000)
measure(np_array_tobytes, 10000000)

print('-' * 40)
