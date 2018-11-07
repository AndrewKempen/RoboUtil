#include "OmniDirectionalPursuit.h"

using namespace std;

OmniDirectionalPursuit::OmniDirectionalPursuit(double fixedLookahead, double maxAccel, double rotationkP, double nominalDt, Path path, bool reversed,
                                 double pathCompletionTolerance, bool gradualStop) :
    m_lastCommand(0, 0, 0) {
    m_fixedLookahead = fixedLookahead;
    m_maxAccel = maxAccel;
    m_rotationkP = rotationkP;
    m_path = path;
    m_dt = nominalDt;
    m_reversed = reversed;
    m_pathCompletionTolerance = pathCompletionTolerance;
    m_lastTime = 0.0;
    m_gradualStop = gradualStop;
}

bool OmniDirectionalPursuit::isDone() {
    double remainingLength = m_path.getRemainingLength();
    return (remainingLength <= m_pathCompletionTolerance);
}

Position2d::Delta OmniDirectionalPursuit::update(Position2d robotPos, double now) {
    Position2d pos = robotPos;
    if (m_reversed) {
        pos = Position2d(robotPos.getTranslation(), robotPos.getRotation().rotateBy(Rotation2d::fromRadians(PI)));
    }

    double distanceFromPath = m_path.update(pos.getTranslation());
    if (isDone()) {
        return {0, 0, 0};
    }

    PathSegment::Sample lookaheadPoint = m_path.getLookaheadPoint(pos.getTranslation(),
                                                                  distanceFromPath + m_fixedLookahead);

    double speed = lookaheadPoint.speed;
    if (m_reversed) {
        speed *= -1;
    }

    double dt = now - m_lastTime;
    if (!m_hasRun) {
        m_lastCommand = Position2d::Delta(0, 0, 0);
        dt = m_dt;
        m_hasRun = true;
    }
    double lastSpeed = hypot(m_lastCommand.dx, m_lastCommand.dy) * 100;
    double accel = (speed - lastSpeed) / dt;
    if (accel < -m_maxAccel) {
        speed = lastSpeed - m_maxAccel * dt;
    } else if (accel > m_maxAccel) {
        speed = lastSpeed + m_maxAccel * dt;
    }

    double remainingDistance = m_path.getRemainingLength() - 6;
    remainingDistance = remainingDistance < 0 ? 0 : remainingDistance;
    double maxAllowedSpeed = sqrt(2 * m_maxAccel * remainingDistance);
    if (fabs(speed) > maxAllowedSpeed) {
        speed = maxAllowedSpeed * (speed / fabs(speed));
    }


    Position2d::Delta rv(0, 0, 0);

    Translation2d move = robotPos.getTranslation().inverse().translateBy(lookaheadPoint.translation);
    double x = move.getCos() * speed * 0.01;
    double y = move.getSin() * speed * 0.01;

    Rotation2d setAngle = m_path.getClosestPoint(pos.getTranslation()).getRotation();

    double remainingAng = Vector::FromRadians(robotPos.getRotation().getRadians())
            .ShortestRotationTo(Vector::FromRadians(setAngle.getRadians()));

    double angSpeed = remainingAng * m_rotationkP;

    rv = Position2d::Delta(x, y, angSpeed);
    m_lastTime = now;
    m_lastCommand = rv;
    return rv;
}

bool OmniDirectionalPursuit::checkEvent(string event) {
    return m_path.eventPassed(event);
}

OmniDirectionalPursuit::Circle::Circle(Translation2d cent, double rad, bool turn_right) {
    center = cent;
    radius = rad;
    turnRight = turn_right;
}

pair<bool, OmniDirectionalPursuit::Circle> OmniDirectionalPursuit::joinPath(Position2d pos, Translation2d lookahead) {
    double x1 = pos.getTranslation().getX();
    double y1 = pos.getTranslation().getY();
    double x2 = lookahead.getX();
    double y2 = lookahead.getY();

    Translation2d posToLookahead = pos.getTranslation().inverse().translateBy(lookahead);

    double crossProduct = lookahead.getX() * pos.getRotation().getSin()
                          - posToLookahead.getY() * pos.getRotation().getCos();
    if (abs(crossProduct) < kE) {
        return {false, Circle(Translation2d(), 0, 0)};
    }

    double dx = x1 - x2;
    double dy = y1 - y2;
    double my = ((crossProduct > 0) ? -1 : 1) * pos.getRotation().getCos();
    double mx = ((crossProduct > 0) ? 1 : -1) * pos.getRotation().getSin();

    double crossTerm = mx * dx + my * dy;

    if (abs(crossTerm) < kE) {
        return {false, Circle(Translation2d(), 0, false)};
    }

    return {true, Circle(Translation2d((mx * (x1 * x1 - x2 * x2 - dy * dy) + 2 * my * x1 * dy) / (2 * crossTerm),
                                       (-my * (-y1 * y1 + y2 * y2 + dx * dx) + 2 * mx * y1 * dx) / (2 * crossTerm)),
                         .5 * abs((dx * dx + dy * dy) / crossTerm), (crossProduct > 0))};
}
