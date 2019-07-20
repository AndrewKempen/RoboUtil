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

    tankOdometry->Setup(returnZero, returnZero, returnZeroAngle, 0.1);
    tankOdometry->Start();
    sleep(5);
    tankOdometry->Stop();
    EXPECT_EQ(true, true);
}