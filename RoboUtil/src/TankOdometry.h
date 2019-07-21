#pragma once

#include "Math/Angle.h"
#include "Math/Pose.h"
#include "Math/Point.h"
#include "Math/Vector.h"
#include "Math.h"

using namespace std;


class TankOdometry {
public:
    struct EncoderConfig {
        double initialTicks;
        double ticksPerWheelRevolution;
        double wheelDiameter;
    };

    void ResetEncoderTicks(double leftEncoderTicks = 0, double rightEncoderTicks = 0);
    void Update(double leftEncoderRawTicks, double rightEncoderRawTicks, Angle gyroAngle);

    static TankOdometry* GetInstance();

    void Initialize(EncoderConfig leftEncoderConfig, EncoderConfig rightEncoderConfig, Pose currentPose = Pose());

    void SetCurrentPose(Pose currentPose);

private:
    double m_leftTicksToDist;
    double m_rightTicksToDist;

    double m_lastLeftEncoderDist;
    double m_lastRightEncoderDist;

    Angle m_gyroInitialAngle;

    bool m_poseReset = true;

    Pose m_robotPose = Pose(Point(), Angle());

    static TankOdometry* m_instance;
};


