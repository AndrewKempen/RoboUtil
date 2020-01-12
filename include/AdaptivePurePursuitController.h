#pragma once

#include "Math/Pose.h"
#include "Math/Math.h"
#include "Path.h"

struct DriveCommand {
    double rightVelocity;
    double leftVelocity;
};

class AdaptivePurePursuitController {
private:
    Path m_path;
    double m_lookaheadDistance;
    double m_maxAccel;
    double m_trackWidth;
    double m_completionTolerance;
    double m_lastTime = -1;
    double m_lastVelocity = -1;

public:
    AdaptivePurePursuitController(Path path, double lookaheadDistance, double trackWidth,
                                  double pathCompletionTolerance, double maxAccel);
    DriveCommand Update(Pose robotPose, double currentTime);

};


