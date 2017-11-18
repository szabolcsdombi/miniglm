import time
from miniglm import Mat3, Vec3, Quat

rot = (0.445, 0.801, 0.317, -0.246)
v1 = (1.0, 0.0, 0.0)
v2 = (0.0, 1.0, 0.0)
v3 = (0.0, 0.0, 1.0)

start = time.clock()

for i in range(1000000):
    m = Mat3(Quat(rot))      # tuple -> quaternion, quaternion -> matrix
    m = m * m * m            # matrix multiplication, matrix multiplication, matrix multiplication
    a = m * Vec3(v1) * 2.0   # tuple -> vector, matrix * vector, vector * scalar
    b = m * Vec3(v2) * 3.0   # tuple -> vector, matrix * vector, vector * scalar
    c = m * Vec3(v3) * 4.0   # tuple -> vector, matrix * vector, vector * scalar
    d = (a + b + c) / 10.0   # vector + vector, vector + vector, vector / scalar
    res = d.tup              # vector -> tuple

end = time.clock()

print(end - start, 'seconds')
