#pragma once

#include "Point.h"

struct Pose {
    Point point;
    Angle angle;

    Pose();
	Pose(Point point, Angle angle);
};
