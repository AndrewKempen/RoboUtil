#include "AdaptivePurePursuitController.h"

AdaptivePurePursuitController::AdaptivePurePursuitController(Path path, double lookaheadDistance, double maxAccel, double trackWidth,
                                                             double pathCompletionTolerance) : m_path(path) {
    m_lookaheadDistance = lookaheadDistance;
    m_maxAccel = maxAccel;
    m_trackWidth = trackWidth;
    m_completionTolerance = pathCompletionTolerance;
}

AdaptivePurePursuitController::DriveCommand AdaptivePurePursuitController::Update(Pose robotPose) {
    double distanceFromPath = m_path.update(robotPose.position);

    if(m_path.GetDistanceRemaining() < m_completionTolerance) {
        DriveCommand command;
        command.rightVelocity = 0;
        command.leftVelocity = 0;
        return command;
    }

    double lookaheadDistance = distanceFromPath + m_lookaheadDistance;

    Vector2d lookaheadPoint = m_path.findCircularIntersection(robotPose.position, lookaheadDistance);

    Vector2d robotToLookahead = lookaheadPoint - robotPose.position;

    Vector2d robotPoseUnitVector = robotPose.angle * Vector2d::UnitX();

    Vector2d robotToPerpIntersection = robotPoseUnitVector.dot(robotToLookahead) * robotPoseUnitVector;

    Vector2d perpIntersectionToLookahead = robotToLookahead - robotToPerpIntersection;

    double curvature = 2 * perpIntersectionToLookahead.norm() / (lookaheadDistance * lookaheadDistance);

    curvature *= robotToLookahead.x() * sin(robotPose.angle.angle())
            - robotToLookahead.y() * cos(robotPose.angle.angle()) > 0 ? 1 : -1;

    double velocity = 1;

    DriveCommand command;

    command.leftVelocity = velocity * (2 + curvature * m_trackWidth) / 2;
    command.rightVelocity = velocity * (2 + curvature * m_trackWidth) / 2;

    return command;
}
