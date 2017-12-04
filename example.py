import miniglm as glm
import ModernGL
import numpy as np
from ModernGL.ext.examples import run_example


def grid(size, steps):
    u = np.repeat(np.linspace(-size, size, steps), 2)
    v = np.tile([-size, size], steps)
    w = np.zeros(steps * 2)
    return np.concatenate([np.dstack([u, v, w]), np.dstack([v, u, w])])


class Example:
    def __init__(self, wnd):
        self.wnd = wnd
        self.ctx = ModernGL.create_context()

        self.prog = self.ctx.program([
            self.ctx.vertex_shader('''
                #version 330

                uniform mat4 Mvp;

                in vec3 in_vert;

                void main() {
                    gl_Position = Mvp * vec4(in_vert, 1.0);
                }
            '''),
            self.ctx.fragment_shader('''
                #version 330

                out vec4 f_color;

                void main() {
                    f_color = vec4(0.1, 0.1, 0.1, 1.0);
                }
            '''),
        ])

        self.mvp = self.prog.uniforms['Mvp']

        self.vbo = self.ctx.buffer(grid(15, 10).astype('f4').tobytes())
        self.vao = self.ctx.simple_vertex_array(self.prog, self.vbo, ['in_vert'])

    def render(self):
        width, height = self.wnd.size
        self.ctx.viewport = self.wnd.viewport
        self.ctx.clear(1.0, 1.0, 1.0)
        self.ctx.enable(ModernGL.DEPTH_TEST)

        proj = glm.mat4_perspective(glm.radians(60.0), width / height, 0.1, 1000.0)
        lookat = glm.mat4_look_at(
            (40.0, 30.0, 30.0),
            (0.0, 0.0, 0.0),
            (0.0, 0.0, 1.0),
        )

        self.mvp.write(proj * lookat)
        self.vao.render(ModernGL.LINES)


run_example(Example)
