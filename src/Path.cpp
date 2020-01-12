#include "Path.h"
#include "../include/Path.h"

Path::Path(string name, vector<Waypoint> waypoints) {
    m_name = name;
    m_waypoints = waypoints;

    m_length = 0;

    for(unsigned int i = 0; i < m_waypoints.size() - 1; i++) {
        PathSegment segment = PathSegment(m_waypoints[i], m_waypoints[i + 1]);
        m_pathSegments.push_back(segment);
        m_length += segment.getLength();
    }

    m_currentSegment = 0;
    m_currentSegmentStart = 0;
    if(!m_pathSegments.empty()) {
        m_currentSegmentEnd = m_pathSegments[0].getLength();
    } else {
        m_currentSegmentEnd = 0;
    }
}

void Path::flipOverXAxis() {

}

void Path::flipOverYAxis() {

}

void Path::addWaypoint(Waypoint waypoint) {
    m_waypoints.push_back(waypoint);
}

PathSegment::closestPointReport Path::update(Vector2d robotPosition) {
    PathSegment::closestPointReport report;
    bool closestSegmentFound = false;

    report = m_pathSegments[m_currentSegment].getClosestPoint(robotPosition, m_distanceDownPath - m_currentSegmentStart);

    while (!closestSegmentFound) {
        if (report.distanceToEnd < 0) { //Closest point is beyond current segment
            if (m_currentSegment < m_pathSegments.size() - 1) { //There is another segment for us to check
                m_currentSegmentStart += m_pathSegments[m_currentSegment].getLength();
                m_currentSegment++;
                report = m_pathSegments[m_currentSegment].getClosestPoint(robotPosition, m_distanceDownPath - m_currentSegmentStart);
            } else { //No more segments left, so use current segment
                closestSegmentFound = true;
            }
        } else { //Closest point might be on current segment
            if (m_currentSegment < m_pathSegments.size() - 1) { //Make sure next segment is not closer
                PathSegment::closestPointReport nextReport;
                nextReport = m_pathSegments[m_currentSegment + 1].getClosestPoint(robotPosition, 0);
                if (nextReport.distanceAway < report.distanceAway
                    && nextReport.distanceToStart > 0
                    && nextReport.distanceToEnd > 0) {
                    m_currentSegmentStart += m_pathSegments[m_currentSegment].getLength();
                    m_currentSegment++;
                    report = nextReport;
                } else { //Next segment is farther away, so it must be this segment
                    closestSegmentFound = true;
                }
            } else { //Hurray! Closest point is on this segment!
                closestSegmentFound = true;
            }
        }
    }

    m_distanceDownPath += report.distanceToStart;
    return report;
}

Vector2d Path::findCircularIntersection(Vector2d center, double radius) {
    if (m_pathSegments.empty()) {
        Logger::logError("Path is empty");
        return center;
    }

    Vector2d centerToStart = m_pathSegments[0].getStart() - center;
    if(centerToStart.norm() >= radius) {
        //We are way before first point
        return m_pathSegments[0].getStart();
    }

    for (unsigned int i = m_currentSegment; i < m_pathSegments.size(); i++) {
        PathSegment segment = m_pathSegments[i];
        Vector2d centerToSegmentEnd = center - segment.getEnd();
        if (centerToSegmentEnd.norm() > radius) {
            //Gotcha! Somewhere on this segment must be the circular intersection point
            Vector2d intersectionPoint = segment.getCircularIntersectionPoint(center, radius);

            if(intersectionPoint != center) {
                return intersectionPoint;
            } else {
                Logger::logError("Couldn't find circular intersection point on path!");
            }
        }
    }

    //We might be at the end of the path, so try finding an intersection point by extending the last segment
    PathSegment newLastSegment = m_pathSegments[m_pathSegments.size() - 1];
    newLastSegment.extend(radius);
    Vector2d intersectionPoint = newLastSegment.getCircularIntersectionPoint(center, radius);

    if(intersectionPoint != center) {
        return intersectionPoint;
    } else {
        Logger::logError("Couldn't find circular intersection point even by extending last segment?");
    }
    return center;
}

double Path::GetDistanceRemaining() {
    return m_length - m_distanceDownPath;
}

vector<Waypoint> Path::getWaypoints() {
    return m_waypoints;
}

vector<PathSegment> Path::getPathSegments() {
    return m_pathSegments;
}