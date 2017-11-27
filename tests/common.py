import unittest


class MyTestCase(unittest.TestCase):
    def assertAlmostEqual1(self, first, second, places=None, msg=None, delta=None):
        if places is None:
            places = 4

        self.assertAlmostEqual(first, second, places, msg, delta)

    def assertAlmostEqual2(self, first, second, places=None, msg=None, delta=None):
        self.assertEqual(len(first), len(second))
        for a, b in zip(first, second):
            self.assertAlmostEqual1(a, b, places, msg, delta)
