import struct
import time

from miniglm import Vec3
import numpy as np


def measure(func, *args):
    print('Running %s %r - ' % (func.__name__, args), end='')
    start = time.clock()
    func(*args)
    elapsed = time.clock() - start
    print(elapsed, 'seconds')


def struct_pack1(n):
    x, y, z = 0.0, 0.0, 0.0
    for i in range(n):
        struct.pack('3f', x, y, z)


def struct_pack2(n):
    s = struct.Struct('3f')
    x, y, z = 0.0, 0.0, 0.0
    for i in range(n):
        s.pack(x, y, z)


def vec_to_bytes(n):
    v = Vec3((0.0, 0.0, 0.0))
    for i in range(n):
        bytes(v)


def vec_data(n):
    v = Vec3((0.0, 0.0, 0.0))
    for i in range(n):
        v.data


def np_array_tobytes(n):
    a = np.array((0.0, 0.0, 0.0), dtype='f4')
    for i in range(n):
        a.tobytes()


measure(struct_pack1, 10000000)
measure(struct_pack2, 10000000)
measure(vec_to_bytes, 10000000)
measure(vec_data, 10000000)
measure(np_array_tobytes, 10000000)

print('-' * 40)
