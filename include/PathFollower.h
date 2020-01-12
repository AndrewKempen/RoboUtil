#pragma once

#include "Path.h"
#include "AdaptivePurePursuitController.h"


class PathFollower {
public:
    struct Parameters {
        double lookaheadDist;
        double inertiaGain;
        double profileKp;
        double profileKi;
        double profileKv;
        double profileKffv;
        double profileKffa;
        double profileKs;
        double profileMaxAbsVel;
        double profileMaxAbsAcc;
        double goalPosTol;
        double goalVelTol;
        double stopSteeringDist;
        double trackWidth;
    };
    PathFollower(Path path, Parameters parameters);

    DriveCommand Update(double timestamp, Pose pose, double displacement, double velocity);

    bool IsFinished();

private:
    AdaptivePurePursuitController * m_controller;

};


