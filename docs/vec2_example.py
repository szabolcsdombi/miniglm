# new instance
>>> a = Vec2([3.0, 4.0])
>>> a
(3.0, 4.0)

# length
>>> a.length
5.0

>>> b = Vec2([10.0, 10.0])

# normal
>>> b.normal
(0.7071068286895752, 0.7071068286895752)

# dot product
>>> a.dot(b)
70.0

>>> light = Vec2([1.0, -1.0])

# reflect
>>> light.reflect(Vec2([0.0, 1.0]))
(1.0, 1.0)

# refract
>>> light.refract(Vec2([0.0, 1.0]), 0.0)
(0.0, -1.0)

# refract
>>> light.refract(Vec2([0.0, 1.0]), 1.0)
(1.0, -1.0)

# unpack
>>> x, y = a

# convert to list
>>> list(a)
[3.0, 4.0]

# convert to bytes
>>> bytes(a)
b'\x00\x00@@\x00\x00\x80@'

# basic math
>>> c = a + b * 2.0
>>> c
(23.0, 24.0)

# indexing
>>> c[1]
24.0

# element-wise multiplication
>>> a * a
(9.0, 16.0)
