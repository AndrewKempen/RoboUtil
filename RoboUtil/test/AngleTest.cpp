#include "gtest/gtest.h"
#include "Math/Angle.h"

TEST(AngleTest, CheckRotateBy) {
    Angle firstAngle = Angle::fromDegrees(33);
    Angle secondAngle;

    secondAngle = Angle::fromDegrees(327); //360 - 33
    EXPECT_NEAR(firstAngle.getRotateBy(secondAngle).getDegrees(), 0, 0.005);

    secondAngle = Angle::fromDegrees(-60);
    EXPECT_NEAR(firstAngle.getRotateBy(secondAngle).getDegrees(), -27, 0.005); //33 - 60

    secondAngle = Angle::fromDegrees(35);
    EXPECT_NEAR(firstAngle.getRotateBy(secondAngle).getDegrees(), 68, 0.005); //33 + 35
}
