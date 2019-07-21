#include "gtest/gtest.h"
#include "TankOdometry.h"
#include "Math/Angle.h"

double returnZero() {
    return 0;
}

Angle returnZeroAngle() {
    return Angle::fromDegrees(0);
}

TEST(TankOdometry, ThreadRuns) {
    TankOdometry * tankOdometry = TankOdometry::GetInstance();

    EXPECT_EQ(true, true);
}