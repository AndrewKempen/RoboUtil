#include "PathFollower.h"

PathFollower::PathFollower(Path path, PathFollower::Parameters parameters) {
    m_controller = new AdaptivePurePursuitController(path, parameters.lookaheadDist,
                                                     parameters.trackWidth, parameters.goalPosTol, 0);
}

DriveCommand PathFollower::Update(double timestamp, Pose pose, double displacement, double velocity) {
    return DriveCommand();
}

bool PathFollower::IsFinished() {
    return false;
}
