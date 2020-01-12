#pragma once

#include "Waypoint.h"
#include "Logger.h"
#include <Eigen/Dense>

using namespace Eigen;

class PathSegment {
private:
    Vector2d m_start, m_end;
    Vector2d m_startToEnd;
    Vector2d m_startToEndUnit;
    double m_startSpeed;
    double m_endSpeed;
    double m_distanceToSpeedFactor;
    double m_length, m_lengthSquared;
    string m_stateCommand;

    double getSpeed(double distanceFromStart);

public:
    struct closestPointReport {
        Vector2d closestPoint;
        double distanceToStart;
        double distanceToEnd;
        double distanceAway;
        double speed;
    };
    PathSegment(Waypoint startPoint, Waypoint endPoint);
    Vector2d getStart();
    Vector2d getEnd();
    double getLength();
    closestPointReport getClosestPoint(Vector2d otherPoint, double minimumDistanceFromStart);
    Vector2d getCircularIntersectionPoint(Vector2d center, double radius);
    void extend(double lengthToExtendBy);

    EIGEN_MAKE_ALIGNED_OPERATOR_NEW
};


