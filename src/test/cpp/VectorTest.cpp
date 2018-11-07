#include "gtest/gtest.h"
#include "Vector.h"

TEST(VectorTest, Initialization) {
    Vector vector1 = Vector::FromXY(1, 2);
    EXPECT_DOUBLE_EQ(vector1.GetX(), 1);
    EXPECT_DOUBLE_EQ(vector1.GetY(), 2);

    vector1 = Vector::FromRadians(toRadians(45), sqrt(2));
    EXPECT_DOUBLE_EQ(vector1.GetX(), 1);
    EXPECT_DOUBLE_EQ(vector1.GetY(), 1);

    vector1 = Vector::FromDegrees(45, sqrt(2));
    EXPECT_DOUBLE_EQ(vector1.GetX(), 1);
    EXPECT_DOUBLE_EQ(vector1.GetY(), 1);

    vector1 = Vector::FromCompassDegrees(0, 1);
    EXPECT_NEAR(vector1.GetX(), 0, 0.001);
    EXPECT_NEAR(vector1.GetY(), 1, 0.001);
}

TEST(VectorTest, Math) {
    Vector vector1 = Vector::FromXY(1, 2);
    Vector vector2 = Vector::FromXY(1, 0);

    vector1.AddVector(vector2);
    EXPECT_DOUBLE_EQ(vector1.GetX(), 2);
    EXPECT_DOUBLE_EQ(vector1.GetY(), 2);

    vector1.SubtractVector(vector2);
    EXPECT_DOUBLE_EQ(vector1.GetX(), 1);
    EXPECT_DOUBLE_EQ(vector1.GetY(), 2);
}