#pragma once

#include <functional>
#include <thread>
#include <memory>
#include <chrono>
#include <atomic>
#include "Math/Angle.h"
#include "Math/Position.h"
#include "Math/Point.h"
#include "Math/Vector.h"

using namespace std;


class TankOdometry {
public:
    void Setup(function<double(void)> getLeftEncoderInches, function<double(void)> getRightEncoderInches, function<Angle(void)> getGyroAngle, double updateRate);
    void Start();
    void Stop();
    void Update();

    static TankOdometry* GetInstance();

private:


    Position m_robotPosition = Position(Point(), Angle());

    function<double(void)> m_getLeftEncoderInches;
    function<double(void)> m_getRightEncoderInches;
    function<Angle(void)> m_getGyroAngle;

    shared_ptr<thread> m_updateThread;

    double m_updateRate;

    static TankOdometry* m_instance;

    atomic<bool> m_running;
};


