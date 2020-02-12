#include "AdaptivePurePursuitController.h"

AdaptivePurePursuitController::AdaptivePurePursuitController(Path path, double lookaheadDistance, double trackWidth,
                                                             double pathCompletionTolerance, double maxAccel) : m_path(path) {
    m_lookaheadDistance = lookaheadDistance;
    m_trackWidth = trackWidth;
    m_completionTolerance = pathCompletionTolerance;
    m_maxAccel = maxAccel;
}

DriveCommand AdaptivePurePursuitController::Update(Pose robotPose, double currentTime) {
    auto report = m_path.update(robotPose.position);

    double distanceFromPath = report.distanceAway;

    if(m_path.GetDistanceRemaining() < m_completionTolerance) {
        DriveCommand command;
        command.rightVelocity = 0;
        command.leftVelocity = 0;
        return command;
    }

    cout << "robotPose: " << robotPose.position << endl;

    double lookaheadDistance = distanceFromPath + m_lookaheadDistance;

    Vector2d lookaheadPoint = m_path.findCircularIntersection(robotPose.position, lookaheadDistance);
    cout << "lookaheadPoint: " << lookaheadPoint << endl;

    Vector2d robotToLookahead = lookaheadPoint - robotPose.position;
    cout << "robotToLookahead: " << robotToLookahead << endl;

    Vector2d robotPoseUnitVector = robotPose.angle * Vector2d::UnitY();

    Vector2d robotToPerpIntersection = robotPoseUnitVector.dot(robotToLookahead) * robotPoseUnitVector;
    cout << "robotToPerpIntersection: " << robotToPerpIntersection << endl;

    Vector2d perpIntersectionToLookahead = robotToLookahead - robotToPerpIntersection;
    cout << "perpIntersectionToLookahead: " << perpIntersectionToLookahead << endl;

    double curvature = 2 * perpIntersectionToLookahead.norm() / (lookaheadDistance * lookaheadDistance);

    cout << "Angle : " << robotPose.angle.angle() << endl;

    double x = robotToLookahead.x();
    double y = robotToLookahead.y();
    double angle = robotPose.angle.angle();

    double velocity = report.speed;

    cout << velocity;

    cout << "," << curvature << ",";

    curvature *= (robotToLookahead.x() * cos(robotPose.angle.angle())
            - robotToLookahead.y() * sin(robotPose.angle.angle())) > 0 ? 1 : -1;

    cout << curvature << ",";

    cout << x << "," << y << "," << angle << ",";

//    if(m_lastTime == -1) {
//        m_lastTime = currentTime;
//        m_lastVelocity = 0;
//        velocity = 0;
//    } else {
//        double deltaTime = currentTime - m_lastTime;
//        double acceleration = (velocity - m_lastVelocity) / deltaTime;
//        if(acceleration >= 0 && acceleration > m_maxAccel) { //Accelerating
//            velocity = m_lastVelocity + m_maxAccel * deltaTime;
//        } else if (-acceleration > m_maxAccel) { //Decelerating
//            velocity = m_lastVelocity + -m_maxAccel * deltaTime;
//        }
//
//        m_lastVelocity = velocity;
//        m_lastTime = currentTime;
//    }
    cout << velocity << ",\n";

    DriveCommand command;

    command.leftVelocity = velocity * (2 + curvature * m_trackWidth) / 2.0;
    command.rightVelocity = velocity * (2 - curvature * m_trackWidth) / 2.0;

    return command;
}
