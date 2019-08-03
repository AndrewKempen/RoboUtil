#include "PathSegment.h"

PathSegment::PathSegment(Waypoint startPoint, Waypoint endPoint) {
    m_start = startPoint.getPoint();
    m_end = endPoint.getPoint();

    //Pre-calculate to increase speed
    m_startToEnd = m_end - m_start;
    m_length = m_startToEnd.norm();
    m_startToEndUnit = m_startToEnd / m_length

    m_startSpeed = startPoint.getSpeed();
    m_endSpeed = endPoint.getSpeed();

    m_distanceToSpeedFactor = (m_endSpeed - m_startSpeed) / m_length;

    m_stateCommand = startPoint.getStateCommand();
}

Vector2d PathSegment::getStart() {
    return m_start;
}

Vector2d PathSegment::getEnd() {
    return m_end;
}

double PathSegment::getLength() {
    return m_length;
}

PathSegment::closestPointReport PathSegment::getClosestPoint(Vector2d otherPoint, double minimumDistanceFromStart) {
    Vector2d startToMinimum = m_startToEndUnit * minimumDistanceFromStart;
    Vector2d minimum = m_start + startToMinimum;
    Vector2d minimumToEnd = m_end - minimum;
    double length = minimumToEnd.norm();

    closestPointReport report;

    if(length > 0) {
        Vector2d startToOther = otherPoint - m_start;
        double distFromMinimum = minimumToEnd.dot(startToOther) / length; //Find component of minimumToEnd vector onto
                                                                          //this path segment
        Vector2d minimumToClosest = minimumToEnd * (distFromMinimum / length);
        report.distanceToStart = minimumDistanceFromStart - distFromMinimum;
        report.distanceToEnd = m_length - report.distanceToStart;
        report.closestPoint = m_start + startToMinimum + minimumToClosest; //Closest point on path segment
    } else {
        report.distanceToEnd = length;
        report.closestPoint = minimum;
    }
    Vector2d closestToOther = otherPoint - report.closestPoint;
    report.distanceAway = closestToOther.norm();
    report.speed = getSpeed(m_length - report.distanceToEnd);
    return report;
}

double PathSegment::getSpeed(double distanceFromStart) {
    return m_startSpeed + distanceFromStart * m_distanceToSpeedFactor;
}

Vector2d PathSegment::getCircularIntersectionPoint(Vector2d center, double radius) {
    //Solution borrowed from https://stackoverflow.com/questions/1073336/circle-line-segment-collision-detection-algorithm/1084899#1084899

    Vector2d centerToStart = m_start - center;
    double a = m_startToEnd.dot(m_startToEnd);
    double b = 2 * centerToStart.dot(m_startToEnd);
    double c = centerToStart.dot(centerToStart) - (radius * radius);
    double discriminant = (b * b) - (4 * a * c);

    if (discriminant < 0) {
        return center; //No intersection
    } else {
        discriminant = sqrt(discriminant);

        double solution1 = (-b - discriminant) / (2 * a);
        if (solution1 >= 0 && solution1 <= 1) {
            return m_start + solution1 * m_startToEnd;
        }

        double solution2 = (-b + discriminant) / (2 * a);
        if (solution2 >= 0 && solution2 <= 1) {
            return m_start + solution2 * m_startToEnd;
        }

        return center; //No intersection exists
    }
}

void PathSegment::extend(double lengthToExtendBy) {
    m_end += m_startToEndUnit * lengthToExtendBy;
}
