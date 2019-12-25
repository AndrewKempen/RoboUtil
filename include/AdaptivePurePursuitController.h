#pragma once

#include "Math/Pose.h"
#include "Path.h"

class AdaptivePurePursuitController {
private:
    Path m_path;
    double m_lookaheadDistance;
    double m_maxAccel;
    double m_trackWidth;
    double m_completionTolerance;

public:
    struct DriveCommand {
        double rightVelocity;
        double leftVelocity;
    };
    AdaptivePurePursuitController(Path path, double lookaheadDistance, double maxAccel, double trackWidth, double pathCompletionTolerance);
    DriveCommand Update(Pose robotPose);

};


