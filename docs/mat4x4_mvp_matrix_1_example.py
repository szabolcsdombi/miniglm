from miniglm import mat4_perspective, mat4_look_at, radians

proj = mat4_perspective(radians(45.0), 16.0 / 9.0, 0.1, 1000.0)
look = mat4_look_at(
    (3.0, 2.0, 1.0),
    (0.0, 0.0, 0.0),
    (0.0, 0.0, 1.0),
)

mvp = proj * look
