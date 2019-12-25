#pragma once

#include <string>
#include <vector>

#include "Logger.h"
#include "PathSegment.h"
#include "Waypoint.h"
#include "json.hpp"

using namespace nlohmann;
using namespace std;

class Path {
private:
    vector<Waypoint> m_waypoints;
    vector<PathSegment> m_pathSegments;
    string m_name;
    double m_length;
    double m_distanceDownPath;
    double m_currentSegmentStart, m_currentSegmentEnd;
    int m_currentSegment;
public:
    Path(string name, vector<Waypoint> waypoints);
    double update(Vector2d robotPosition);
    Vector2d findCircularIntersection(Vector2d center, double radius);
    double GetDistanceRemaining();
    void flipOverXAxis();
    void flipOverYAxis();
    void addWaypoint(Waypoint waypoint);
};


