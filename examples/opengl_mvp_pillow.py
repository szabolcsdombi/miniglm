from PIL import Image, ImageDraw
from miniglm import mat4_perspective, mat4_look_at, Vec4

cube = [
    (-1, -1, -1),
    (-1, -1, +1),
    (-1, +1, -1),
    (-1, +1, +1),
    (+1, -1, -1),
    (+1, -1, +1),
    (+1, +1, -1),
    (+1, +1, +1),
]

edges = [
    (0, 1),
    (1, 3),
    (3, 2),
    (2, 0),
    (4, 5),
    (5, 7),
    (7, 6),
    (6, 4),
    (0, 4),
    (1, 5),
    (2, 6),
    (3, 7),
]

proj = mat4_perspective(60.0 * 3.14 / 180.0, 1.0, 0.1, 10.0)
look = mat4_look_at((4.0, 3.0, 2.0), (0.0, 0.0, 0.0), (0.0, 0.0, 1.0))

verts = [proj * look * Vec4((*vert, 1.0)) for vert in cube]

img = Image.new('L', (256, 256), 'black')
draw = ImageDraw.Draw(img)

for a, b in edges:
    x1, y1, z1, w1 = verts[a]
    x2, y2, z2, w2 = verts[b]
    draw.line((x1 / z1 * 128 + 128, -y1 / z1 * 128 + 128, x2 / z2 * 128 + 128, -y2 / z2 * 128 + 128), 'white')

img.show()
