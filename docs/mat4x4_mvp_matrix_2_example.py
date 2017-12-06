from miniglm import mat4_ortho, mat4_look_at, radians

proj = mat4_ortho(-10.0, 10.0, -10.0, 10.0, 0.1, 1000.0)
look = mat4_look_at(
    (0.0, 0.0, 100.0),
    (0.0, 0.0, 0.0),
    (0.0, 1.0, 0.0),
)

mvp = proj * look
