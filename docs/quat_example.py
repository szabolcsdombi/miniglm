# new instance
>>> a = Quat([0.0, 0.0, 0.0, 1.0])
>>> a
(0.0, 0.0, 0.0, 1.0)

# new instance from a matrix
>>> m = Mat3([1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0])
>>> q = Quat(m)
>>> q
(0.0, 0.0, 0.0, 1.0)
