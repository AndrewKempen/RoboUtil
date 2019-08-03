#pragma once

#include <Eigen/Dense>
#include "Math/Angle.h"

using namespace Eigen;

struct Pose {
    Vector2d position;
    Rotation2Dd angle;

    Pose();
	Pose(Vector2d point, Rotation2Dd angle);
};
