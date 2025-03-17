#include <cmath>
#include <iostream>

const double M_PI = 3.14159265358979323846;

class Circle {
public:
    Circle(double x = 0, double y = 0, double radius = 1)
        : x(x), y(y), radius(radius) {}

    double getX() const { return x; }
    double getY() const { return y; }
    double getRadius() const { return radius; }

    double area() const {
        return M_PI * radius * radius;
    }

    double perimeter() const {
        return 2 * M_PI * radius;
    }

    int point_inside(double px, double py, double tolerance = 1e-6) const {
        double distance = std::sqrt((px - x) * (px - x) + (py - y) * (py - y));
        if (distance < radius - tolerance) {
            return 1;
        }
        else if (std::abs(distance - radius) < tolerance) {
            return 0;
        }
        else {
            return -1;
        }
    }

private:
    double x, y, radius;
};
