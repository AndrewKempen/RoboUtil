#include "gtest/gtest.h"
#include "PathManager.h"
#include "Math/Pose.h"
#include "TankOdometry.h"
#include "AdaptivePurePursuitController.h"

TEST(AdaptivePurePursuit, FollowsStraightPath) {
    PathManager::GetInstance()->LoadPathsFile("test/testPaths/simplePath.json");

    auto paths = PathManager::GetInstance()->GetPaths();

    AdaptivePurePursuitController controller(paths[0], 4, 10.3, 0.01, 0.5);

    TankOdometry::EncoderConfig encoderConfig;

    encoderConfig.initialTicks = 0;
    encoderConfig.ticksPerWheelRevolution = 1;
    encoderConfig.wheelDiameter = (1 / PI);

    TankOdometry::GetInstance()->Initialize(encoderConfig, encoderConfig,
            Pose(paths[0].getWaypoints()[0].getPoint(), Rotation2Dd(0)));

    double leftPosition = 0;
    double rightPosition = 0;

    const double dt = 0.1;

    for(double t = dt; t < 25; t += dt) {
        auto command = controller.Update(TankOdometry::GetInstance()->GetPose(), t);

        leftPosition += (command.leftVelocity * dt);
        rightPosition += (command.rightVelocity * dt);

        TankOdometry::GetInstance()->Update(leftPosition, rightPosition, 10);
    }

    Pose pose = TankOdometry::GetInstance()->GetPose();

    EXPECT_NEAR(pose.position.y(), 71.0, 0.1);
    EXPECT_NEAR(pose.position.x(), 0.0, 0.02);
}

TEST(DISABLED_AdaptivePurePursuit, FollowsSplinePath) {
    PathManager::GetInstance()->LoadPathsFile("test/testPaths/simplePath.json");

    auto paths = PathManager::GetInstance()->GetPaths();

    AdaptivePurePursuitController controller(paths[1], 4, 10.3, 0.01, 0.5);

    TankOdometry::EncoderConfig encoderConfig;

    encoderConfig.initialTicks = 0;
    encoderConfig.ticksPerWheelRevolution = 1;
    encoderConfig.wheelDiameter = (1 / PI);

    TankOdometry::GetInstance()->Initialize(encoderConfig, encoderConfig,
                                            Pose(paths[1].getWaypoints()[0].getPoint(), Rotation2Dd(0)));

    double leftPosition = 0;
    double rightPosition = 0;

    const double dt = 0.1;

    for(double t = dt; t < 100; t += dt) {
        auto command = controller.Update(TankOdometry::GetInstance()->GetPose(), t);

        leftPosition += (command.leftVelocity * dt);
        rightPosition += (command.rightVelocity * dt);

        TankOdometry::GetInstance()->Update(leftPosition, rightPosition, 10.3);
    }

    Pose pose = TankOdometry::GetInstance()->GetPose();

    EXPECT_NEAR(pose.position.x(), -22.2, 0.1);
    EXPECT_NEAR(pose.position.y(), 38.07, 0.1);
}