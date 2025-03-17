import math


class Circle:
    def __init__(self, x=0, y=0, radius=1):
        self.x = x
        self.y = y
        self.radius = radius

    def area(self):
        return math.pi * self.radius**2

    def perimeter(self):
        return 2 * math.pi * self.radius

    def point_inside(self, px, py, tolerance=1e-6):
        distance = math.sqrt((px - self.x) ** 2 + (py - self.y) ** 2)
        if distance < self.radius - tolerance:
            return 1
        elif abs(distance - self.radius) < tolerance:
            return 0
        else:
            return -1
