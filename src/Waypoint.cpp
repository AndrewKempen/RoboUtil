#include "Waypoint.h"

Waypoint::Waypoint(Vector2d point, double speed, string stateCommand) {
    m_point = point;
    m_speed = speed;
    m_stateCommand = stateCommand;
}

Vector2d Waypoint::getPoint() {
    return m_point;
}

double Waypoint::getSpeed() {
    return m_speed;
}

string Waypoint::getStateCommand() {
    return m_stateCommand;
}
