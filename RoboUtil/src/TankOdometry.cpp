#include "TankOdometry.h"

TankOdometry* TankOdometry::m_instance = nullptr;

void TankOdometry::Setup(function<double(void)> getLeftEncoderInches, function<double(void)> getRightEncoderInches,
                           function<Angle(void)> getGyroAngle, double updateRate) {
    m_getLeftEncoderInches = getLeftEncoderInches;
    m_getRightEncoderInches = getRightEncoderInches;
    m_getGyroAngle = getGyroAngle;
    m_updateRate = updateRate;
}


TankOdometry * TankOdometry::GetInstance() {
    if(!m_instance) {
        m_instance = new TankOdometry;
    }
    return m_instance;
}

/*
 * Starts tracking thread
 */
void TankOdometry::Start() {
    m_running = true;
    m_updateThread = make_shared<thread>(&TankOdometry::Update, TankOdometry::GetInstance());
}

/*
 * Stops tracking thread
 */
void TankOdometry::Stop() {
    if(m_running) {
        m_running = false;
        m_updateThread->join();
    }
}

void TankOdometry::Update() {
    while(m_running) {
        double distanceMoved = (m_getLeftEncoderInches() + m_getRightEncoderInches()) / 2.0;
        Angle gyroAngle = m_getGyroAngle();
        Vector robotTranslation = Vector::FromXY(distanceMoved * gyroAngle.getCos(),
                                                 distanceMoved * gyroAngle.getSin());
        m_robotPosition.point.transformBy(robotTranslation);
        this_thread::sleep_for(chrono::milliseconds((int)(1000 * m_updateRate)));
    }
}

