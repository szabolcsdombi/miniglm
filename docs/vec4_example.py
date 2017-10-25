# new instance
>>> a = Vec4([1.0, 2.0, 3.0, 4.0])
>>> a
(1.0, 2.0, 3.0, 4.0)

# length
>>> a.length
5.4772257804870605

>>> b = Vec4([10.0, 10.0, 10.0, 10.0])

# normal
>>> b.normal
(0.5, 0.5, 0.5, 0.5)

# dot product
>>> a.dot(b)
100.0

>>> light = Vec4([1.0, -2.0, 3.0, -4.0])
>>> up = Vec4([0.0, 0.0, 0.0, 1.0])

# reflect
>>> light.reflect(up)
(1.0, -2.0, 3.0, 4.0)

# refract
>>> light.refract(up, 0.0)
(0.0, -0.0, 0.0, -1.0)

# refract
>>> light.refract(up, 1.0)
(1.0, -2.0, 3.0, -4.0)

# unpack
>>> x, y, z, w = a

# convert to list
>>> list(a)
[1.0, 2.0, 3.0, 4.0]

# convert to bytes
>>> bytes(a)
b'\x00\x00\x80?\x00\x00\x00@\x00\x00@@\x00\x00\x80@'

# basic math
>>> c = a + b * 2.0
>>> c
(21.0, 22.0, 23.0, 24.0)

# indexing
>>> c[1]
22.0

# element-wise multiplication
>>> a * a
(1.0, 4.0, 9.0, 16.0)
