import unittest
from circle import Circle


class TestCircle(unittest.TestCase):
    def setUp(self):
        self.default_circle = Circle()
        self.two_param_circle = Circle(3, 4)
        self.three_param_circle = Circle(1, 2, 3)

    def test_default_constructor(self):
        self.assertAlmostEqual(self.default_circle.x, 0.0, places=6)
        self.assertAlmostEqual(self.default_circle.y, 0.0, places=6)
        self.assertAlmostEqual(self.default_circle.radius, 1.0, places=6)

    def test_two_param_constructor(self):
        self.assertAlmostEqual(self.two_param_circle.x, 3.0, places=6)
        self.assertAlmostEqual(self.two_param_circle.y, 4.0, places=6)
        self.assertAlmostEqual(self.two_param_circle.radius, 1.0, places=6)

    def test_three_param_constructor(self):
        self.assertAlmostEqual(self.three_param_circle.x, 1.0, places=6)
        self.assertAlmostEqual(self.three_param_circle.y, 2.0, places=6)
        self.assertAlmostEqual(self.three_param_circle.radius, 3.0, places=6)

    def test_area(self):
        self.assertAlmostEqual(self.default_circle.area(), 3.141592653589793, places=6)
        self.assertAlmostEqual(
            self.three_param_circle.area(), 28.274333882308138, places=6
        )

    def test_perimeter(self):
        self.assertAlmostEqual(
            self.default_circle.perimeter(), 6.283185307179586, places=6
        )
        self.assertAlmostEqual(
            self.three_param_circle.perimeter(), 18.84955592153876, places=6
        )

    def test_point_inside(self):
        self.assertEqual(self.default_circle.point_inside(0, 0), 1)
        self.assertEqual(self.default_circle.point_inside(1, 0), 0)
        self.assertEqual(self.default_circle.point_inside(2, 0), -1)


if __name__ == "__main__":
    unittest.main()
