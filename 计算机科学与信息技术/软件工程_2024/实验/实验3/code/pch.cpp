//
// pch.cpp
//
#include "pch.h"
#include <gtest/gtest.h>
#include "circle.h"

TEST(CircleTest, DefaultConstructor) {
    Circle default_circle;
    EXPECT_NEAR(default_circle.getX(), 0.0, 1e-6);
    EXPECT_NEAR(default_circle.getY(), 0.0, 1e-6);
    EXPECT_NEAR(default_circle.getRadius(), 1.0, 1e-6);
}

TEST(CircleTest, TwoParamConstructor) {
    Circle two_param_circle(3, 4);
    EXPECT_NEAR(two_param_circle.getX(), 3.0, 1e-6);
    EXPECT_NEAR(two_param_circle.getY(), 4.0, 1e-6);
    EXPECT_NEAR(two_param_circle.getRadius(), 1.0, 1e-6);
}

TEST(CircleTest, ThreeParamConstructor) {
    Circle three_param_circle(1, 2, 3);
    EXPECT_NEAR(three_param_circle.getX(), 1.0, 1e-6);
    EXPECT_NEAR(three_param_circle.getY(), 2.0, 1e-6);
    EXPECT_NEAR(three_param_circle.getRadius(), 3.0, 1e-6);
}

TEST(CircleTest, Area) {
    Circle default_circle;
    Circle three_param_circle(1, 2, 3);
    EXPECT_NEAR(default_circle.area(), 3.141592653589793, 1e-6);
    EXPECT_NEAR(three_param_circle.area(), 28.274333882308138, 1e-6);
}

TEST(CircleTest, Perimeter) {
    Circle default_circle;
    Circle three_param_circle(1, 2, 3);
    EXPECT_NEAR(default_circle.perimeter(), 6.283185307179586, 1e-6);
    EXPECT_NEAR(three_param_circle.perimeter(), 18.84955592153876, 1e-6);
}

TEST(CircleTest, PointInside) {
    Circle default_circle;
    EXPECT_EQ(default_circle.point_inside(0, 0), 1);
    EXPECT_EQ(default_circle.point_inside(1, 0), 0);
    EXPECT_EQ(default_circle.point_inside(2, 0), -1);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
