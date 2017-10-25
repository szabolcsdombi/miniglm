# new instance
>>> a = Vec3([1.0, 2.0, 3.0])
>>> a
(1.0, 2.0, 3.0)

# length
>>> a.length
3.7416574954986572

>>> b = Vec3([10.0, 10.0, 10.0])

# normal
>>> b.normal
(0.5773501992225647, 0.5773501992225647, 0.5773501992225647)

# dot product
>>> a.dot(b)
60.0

# cross product
>>> a.cross(b)
(-10.0, 20.0, -10.0)

>>> light = Vec3([1.0, 0.0, -1.0])
>>> up = Vec3([0.0, 0.0, 1.0])

# reflect
>>> light.reflect(up)
(1.0, 0.0, 1.0)

# refract
>>> light.refract(up, 0.0)
(0.0, 0.0, -1.0)

# refract
>>> light.refract(up, 1.0)
(1.0, 0.0, -1.0)

# unpack
>>> x, y, z = a

# convert to list
>>> list(a)
[1.0, 2.0, 3.0]

# convert to bytes
>>> bytes(a)
b'\x00\x00\x80?\x00\x00\x00@\x00\x00@@'

# basic math
>>> c = a + b * 2.0
>>> c
(21.0, 22.0, 23.0)

# indexing
>>> c[0]
21.0

# element-wise multiplication
>>> a * a
(1.0, 4.0, 9.0)
