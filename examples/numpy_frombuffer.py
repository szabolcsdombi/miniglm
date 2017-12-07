import miniglm as glm
import numpy as np

v = glm.Vec3((0.0, 0.0, 0.0))
a = np.frombuffer(v, 'f4')
a.setflags(write=True)
a[:] = (1.0, 2.0, 3.0)

print(v)
