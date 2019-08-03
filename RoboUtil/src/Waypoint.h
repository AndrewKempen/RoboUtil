#pragma once

#include <Eigen/Dense>

using namespace Eigen;

class Waypoint {
public:
    Waypoint(Vector2d point, double speed, string stateCommand = "");
    Vector2d getPoint();
    double getSpeed();
    string getStateCommand();

private:
    Vector2d m_point;
    double m_speed;
    string m_stateCommand;
};


