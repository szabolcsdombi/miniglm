# new instance
>>> a = Mat2([
...     1.0, 2.0,
...     3.0, 4.0,
... ])

>>> a
(1.0, 2.0, 3.0, 4.0)

# transpose
>>> a.trans
(1.0, 3.0, 2.0, 4.0)

# determinant
>>> a.det
-2.0

# inverse
>>> a.inv
(-2.0, 1.0, 1.5, -0.5)

>>> b = Mat2([
...     1.0, 1.0,
...     0.0, 2.0,
... ])

# matrix * matrix
>>> a * b
(4.0, 6.0, 6.0, 8.0)

# matrix * vector
>>> v = Vec2([1.0, 0.0])
>>> a * v
(1.0, 2.0)

# matrix * float
>>> a * 2.5
(2.5, 5.0, 7.5, 10.0)

# rows
>>> a.row(0)
(1.0, 3.0)

# columns
>>> a.col(0)
(1.0, 2.0)

# bytes
>>> bytes(a)
b'\x00\x00\x80?\x00\x00\x00@\x00\x00@@\x00\x00\x80@'

# indexing
>>> a[2]
3.0
