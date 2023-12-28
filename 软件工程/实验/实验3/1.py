class Point:
    def __init__(self, x=0, y=0):
        self.x = x
        self.y = y


def Coverage(a, b, c):
    p = Point()
    x = 5
    y = 7
    if a > b and b > c:
        a += 1
        x += 6

        if a == 10 or b > 20:
            b += 1
            x = y + 4

        if a < 10 or c == 20:
            b += 2
            y = 4

        a = a + b + 1
        y = x + y

    if a > 5 or c < 10:
        b = c + 5
        x += 1

    p.x = x
    p.y = y
    return p


# Example usage:
result = Coverage(3, 4, 5)
print(f"Point: ({result.x}, {result.y})")
result = Coverage(7, 6, 5)
print(f"Point: ({result.x}, {result.y})")
result = Coverage(9, 6, 5)
print(f"Point: ({result.x}, {result.y})")
result = Coverage(8, 21, 5)
print(f"Point: ({result.x}, {result.y})")
result = Coverage(7, 6, 20)
print(f"Point: ({result.x}, {result.y})")
result = Coverage(9, 21, 20)
print(f"Point: ({result.x}, {result.y})")
result = Coverage(6, 7, 11)
print(f"Point: ({result.x}, {result.y})")
result = Coverage(4, 6, 9)
print(f"Point: ({result.x}, {result.y})")
