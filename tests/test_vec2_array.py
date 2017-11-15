import unittest
import math

from miniglm import Vec2Array


class TestCase(unittest.TestCase):
    def test_example(self):
        a = Vec2Array([1.0, 2.0, 3.0, 4.0])
        b = Vec2Array([1.0, 2.0, 3.0, 4.0])
        print(a + b)



if __name__ == '__main__':
    unittest.main()
