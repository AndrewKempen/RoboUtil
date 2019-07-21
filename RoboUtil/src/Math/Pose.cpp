#include "Math/Pose.h"


Pose::Pose(Point point, Angle angle) {
    point = point;
    angle = angle;
}

Pose::Pose() {
    point = Point();
    angle = Angle();
}
