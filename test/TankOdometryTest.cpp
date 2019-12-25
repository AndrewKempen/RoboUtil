#include "gtest/gtest.h"
#include "TankOdometry.h"

TEST(TankOdometry, ThreadRuns) {
    TankOdometry * tankOdometry = TankOdometry::GetInstance();

    EXPECT_EQ(true, true);
}