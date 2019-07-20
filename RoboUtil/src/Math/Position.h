#pragma once

#include "Point.h"

class Position {
public:
    Point point;
    Angle angle;

	Position(Point point, Angle angle);
};
