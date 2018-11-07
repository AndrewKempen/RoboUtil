#pragma once

#include "Position2d.h"

class PursuitController {
public:
    virtual bool isDone() = 0;
    virtual Position2d::Delta update(Position2d robotPos, double now) = 0;
    virtual bool checkEvent(std::string event) = 0;
};
