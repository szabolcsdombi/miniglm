import time
from miniglm import Vec3
# from pyrr import Vector3
# import numpy as np


class PyVec3:
    def __init__(self, val):
        self.x, self.y, self.z = val

    def __add__(self, other):
        return PyVec3((self.x + other.x, self.y + other.y, self.z + other.z))

    def __mul__(self, other):
        if type(other) is PyVec3:
            return PyVec3((self.x * other.x, self.y * other.y, self.z * other.z))

        else:
            return PyVec3((self.x * other, self.y * other, self.z * other))


def measure(func, *args):
    print('Running %s %r - ' % (func.__name__, args), end='')
    start = time.clock()
    func(*args)
    elapsed = time.clock() - start
    print(elapsed, 'seconds')


def add_mul(typ, a, b, c, n):
    for i in range(n):
        x = typ(a)
        y = typ(b)
        z = x + y + x * y * c


def add_add_add(typ, a, n):
    for i in range(n):
        x = typ(a)
        x = x + x + x + x + x + x + x + x + x + x + x + x + x + x + x + x + x + x + x + x + x
        x = x + x + x + x + x + x + x + x + x + x + x + x + x + x + x + x + x + x + x + x + x
        x = x + x + x + x + x + x + x + x + x + x + x + x + x + x + x + x + x + x + x + x + x
        x = x + x + x + x + x + x + x + x + x + x + x + x + x + x + x + x + x + x + x + x + x
        x = x + x + x + x + x + x + x + x + x + x + x + x + x + x + x + x + x + x + x + x + x


measure(add_mul, Vec3, (0.0, 0.0, 0.0), (0.0, 0.0, 0.0), 0.0, 10000000)
measure(add_mul, PyVec3, (0.0, 0.0, 0.0), (0.0, 0.0, 0.0), 0.0, 10000000)
# measure(add_mul, Vector3, (0.0, 0.0, 0.0), (0.0, 0.0, 0.0), 0.0, 10000000)
# measure(add_mul, np.array, (0.0, 0.0, 0.0), (0.0, 0.0, 0.0), 0.0, 10000000)

print('-' * 40)

measure(add_add_add, Vec3, (0.0, 0.0, 0.0), 1000000)
measure(add_add_add, PyVec3, (0.0, 0.0, 0.0), 1000000)
# measure(add_add_add, Vector3, (0.0, 0.0, 0.0), 1000000)
# measure(add_add_add, np.array, (0.0, 0.0, 0.0), 1000000)

print('-' * 40)
