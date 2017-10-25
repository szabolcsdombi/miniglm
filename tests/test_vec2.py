import unittest
import math

from miniglm import Vec2


class TestCase(unittest.TestCase):
    def test_example(self):
        a = Vec2([3.0, 4.0])

        ax, ay = a
        self.assertAlmostEqual(ax, 3.0)
        self.assertAlmostEqual(ay, 4.0)

        self.assertAlmostEqual(a.length, 5.0)

        b = Vec2([10.0, 10.0])

        bnx, bny = b.normal
        self.assertAlmostEqual(bnx, math.sqrt(2) / 2)
        self.assertAlmostEqual(bny, math.sqrt(2) / 2)

        self.assertAlmostEqual(a.dot(b), 70.0)

        cx, cy = a + b * 2.0
        self.assertAlmostEqual(cx, 23.0)
        self.assertAlmostEqual(cy, 24.0)

        light = Vec2([1.0, -1.0])

        lx1, ly1 = light.reflect(Vec2([0.0, 1.0]))
        self.assertAlmostEqual(lx1, 1.0)
        self.assertAlmostEqual(ly1, 1.0)

        lx2, ly2 = light.refract(Vec2([0.0, 1.0]), 0.0)
        self.assertAlmostEqual(lx2, 0.0)
        self.assertAlmostEqual(ly2, -1.0)

        lx3, ly3 = light.refract(Vec2([0.0, 1.0]), 0.5)
        self.assertAlmostEqual(lx3, 0.5)
        self.assertAlmostEqual(ly3, -1.0)

        lx4, ly4 = light.refract(Vec2([0.0, 1.0]), 1.0)
        self.assertAlmostEqual(lx4, 1.0)
        self.assertAlmostEqual(ly4, -1.0)


if __name__ == '__main__':
    unittest.main()
