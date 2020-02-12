#include "gtest/gtest.h"
#include "PathManager.h"
#include "Math/Pose.h"
#include "TankOdometry.h"
#include "AdaptivePurePursuitController.h"
#include <stdio.h>

TEST(AdaptivePurePursuit, FollowsStraightPath) {
    PathManager::GetInstance()->LoadPathsFile("test/testPaths/simplePath.json");

    auto paths = PathManager::GetInstance()->GetPaths();

    AdaptivePurePursuitController controller(paths[0], 4, 10.3, 0.01, 100);

    TankOdometry::EncoderConfig encoderConfig;

    encoderConfig.initialTicks = 0;
    encoderConfig.ticksPerWheelRevolution = 1;
    encoderConfig.wheelDiameter = (1 / PI);

    TankOdometry::GetInstance()->Initialize(encoderConfig, encoderConfig,
                                            Pose(paths[0].getWaypoints()[0].getPoint(), Rotation2Dd(0)));

    double leftPosition = 0;
    double rightPosition = 0;

    const double dt = 0.1;

    FILE *myfile;

    myfile = fopen("log.csv", "w");

    fprintf(myfile, "time,leftVelocity,rightVelocity,leftPosition,rightPosition,x,y,\n");

    for (double t = dt; t < 25; t += dt) {
        auto command = controller.Update(TankOdometry::GetInstance()->GetPose(), t);

        leftPosition += (command.leftVelocity * dt);
        rightPosition += (command.rightVelocity * dt);

        TankOdometry::GetInstance()->Update(leftPosition, rightPosition, 10);

        fprintf(myfile, "%.1f,%.5f,%.5f,%.5f,%.5f,%.5f,%.5f,\n", t, command.leftVelocity, command.rightVelocity,
                leftPosition, rightPosition, TankOdometry::GetInstance()->GetPose().position.x(),
                TankOdometry::GetInstance()->GetPose().position.y());
    }

    fclose(myfile);

    Pose pose = TankOdometry::GetInstance()->GetPose();

    EXPECT_NEAR(pose.position.y(), 71.0, 0.1);
    EXPECT_NEAR(pose.position.x(), 0.0, 0.02);
}

TEST(AdaptivePurePursuit, FollowsSplinePath) {
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

    FILE *myfile;

    myfile = fopen("log2.csv", "w");

    fprintf(myfile, "time,leftVelocity,rightVelocity,leftPosition,rightPosition,x,y,\n");

    for (double t = dt; t < 25; t += dt) {
        auto command = controller.Update(TankOdometry::GetInstance()->GetPose(), t);

        leftPosition += (command.leftVelocity * dt);
        rightPosition += (command.rightVelocity * dt);

        TankOdometry::GetInstance()->Update(leftPosition, rightPosition, 10);

        fprintf(myfile, "%.1f,%.5f,%.5f,%.5f,%.5f,%.5f,%.5f,\n", t, command.leftVelocity, command.rightVelocity,
                leftPosition, rightPosition, TankOdometry::GetInstance()->GetPose().position.x(),
                TankOdometry::GetInstance()->GetPose().position.y());
    }

    fclose(myfile);

    Pose pose = TankOdometry::GetInstance()->GetPose();

    EXPECT_NEAR(pose.position.x(), -22.2, 0.1);
    EXPECT_NEAR(pose.position.y(), 38.07, 0.1);
}