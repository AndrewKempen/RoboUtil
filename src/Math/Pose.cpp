#include "Math/Pose.h"


Pose::Pose(Vector2d point, Rotation2Dd angle) {
    point = point;
    angle = angle;
}

Pose::Pose() {
    position = Vector2d();
    angle = Rotation2Dd();
}
