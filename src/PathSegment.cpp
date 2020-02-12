#include "PathSegment.h"

PathSegment::PathSegment(Waypoint startPoint, Waypoint endPoint) {
    m_start = startPoint.getPoint();
    m_end = endPoint.getPoint();

    //Pre-calculate to increase speed
    m_startToEnd = m_end - m_start;
    m_length = m_startToEnd.norm();
    m_startToEndUnit = m_startToEnd / m_length;

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
    if(minimumDistanceFromStart > m_length) {
        cout << "Error minimum dist" << endl;
    }
    Vector2d startToMinimum = m_startToEndUnit * minimumDistanceFromStart;
    Vector2d minimum = m_start + startToMinimum;
    Vector2d minimumToEnd = m_end - minimum;
    double length = minimumToEnd.norm();

    closestPointReport report;
    if(length > 0) {
        Vector2d minimumToOther = otherPoint - minimum;

        double dotProduct = minimumToEnd.dot(minimumToOther);
        if (dotProduct <= 0) { //Closest point is behind minimum
            report.distanceToStart = 0;
            report.closestPoint = minimum;
            report.distanceToEnd = length;
        } else {
            Vector2d minimumToClosest = dotProduct / (minimumToEnd.squaredNorm()) * minimumToEnd;

            double distFromMinimum = minimumToClosest.norm();

            report.distanceToStart = distFromMinimum;
            report.distanceToEnd = length - report.distanceToStart;

            report.closestPoint = minimum + minimumToClosest; //Closest point on path segment
        }
    } else {
        report.distanceToEnd = length;
        report.closestPoint = minimum;
        cout << "Error, length < 0" << endl;
    }
    Vector2d closestToOther = otherPoint - report.closestPoint;
    report.distanceAway = closestToOther.norm();
    report.speed = getSpeed(report.distanceToStart + minimumDistanceFromStart);
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

//    Logger::logInfo("Discriminant: " + to_string(discriminant));
//    Logger::logInfo("A: " + to_string(a));
//    Logger::logInfo("B: " + to_string(b));
//    Logger::logInfo("C: " + to_string(c));

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
