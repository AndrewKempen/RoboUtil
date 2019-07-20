#include "Math/Vector.h"

Vector::Vector() {
    m_theta = 0;
    m_r = 0;
}

Vector::Vector(const Vector &other) {
    m_r = other.m_r;
    m_theta = other.m_theta;
}

Vector::Vector(double r, double theta) {
    m_r = r;
    m_theta = theta;
}

Vector Vector::FromRadians(double radians, double mag) {
    return Vector(mag, radians);
}

Vector Vector::FromDegrees(double degrees, double mag) {
    return FromRadians(toRadians(degrees), mag);
}

Vector Vector::FromCompassDegrees(double compassDegrees, double mag) {
    double degrees = 90 - compassDegrees;
    degrees = degrees < 0 ? 360 + degrees : degrees;
    return FromRadians(toRadians(degrees), mag);
}

Vector Vector::FromXY(double x, double y) {
    return Vector(hypot(x, y), atan2(y, x));
}

void Vector::Normalize() {
    if(m_r < 0) {
        Opposite();
    }
    m_r = 1;
}

double Vector::NormalizeMagnitude() {
    m_r = 1;
    return 0;
    //TODO: figure out what this is supposed to do and fix this
}

double Vector::GetRadians() {
    return m_theta;
}

double Vector::GetDegrees() {
    return toDegrees(GetRadians());
}

double Vector::GetCompassDegrees() {
    double degrees = 450 - GetDegrees();
    return (degrees >= 360 ? degrees - 360 : degrees);
}

Vector Vector::RotateBy(Vector other) {
    return Vector(m_r, m_theta + other.m_theta);
}

Vector Vector::RotationInverse() {
    return Vector(m_r, fmod(m_theta + PI, 2 * PI));
}

Vector Vector::Opposite() {
    return Vector(-m_r, fmod(m_theta + PI, 2 * PI));
}

Vector Vector::InterpolateRotation(Vector other, double x) {
    if (x <= 0) {
        return *this;
    } else if (x >= 1) {
        return other;
    }
    double diff = RotationInverse().RotateBy(other).GetRadians();
    return RotateBy(FromRadians(diff * x));
}

double Vector::GetDX() {
    return cos(m_theta) * m_r;
}

double Vector::GetDY() {
    return sin(m_theta) * m_r;
}

void Vector::Invert() {
    m_r *= -1;
    m_theta = fmod(m_theta + PI, 2 * PI);
}

double Vector::GetMagnitude() {
    return m_r;
}

void Vector::SetXY(double x, double y) {
    m_r = hypot(x, y);
    m_theta = atan2(y, x);
}

Vector Vector::TranslateBy(Vector other) {
    return Vector(m_r + other.m_r, m_theta + other.m_theta);
}

Vector Vector::MagnitudeInverse() {
    return Vector(-m_r, m_theta);
}

Vector Vector::InterpolateMagnitude(Vector other, double x) {
    if (x <= 0) {
        return *this;
    } else if (x >= 1) {
        return other;
    }
    return Extrapolate(other, x);
}

Vector Vector::Extrapolate(Vector other, double x) {
    return FromXY(x * (other.GetDX() - GetDX()) + GetDX(), x * (other.GetDY() - GetDY()) + GetDY());
}

Vector Vector::FlipX() {
    //return Vector(-m_x, m_y);
    return Vector(0, 0);
}

Vector Vector::FlipY() {
    //return Vector(m_x, -m_y);
    return Vector(0, 0);
}

void Vector::AddVector(Vector firstVector) {
    SetXY(GetDX() + firstVector.GetDX(), GetDY() + firstVector.GetDY());
}

void Vector::SubtractVector(Vector firstVector) {
    SetXY(GetDX() - firstVector.GetDX(), GetDY() - firstVector.GetDY());
}

double Vector::GetDotProduct(Vector firstVector) {
    return GetDX() * firstVector.GetDX() + GetDY() + firstVector.GetDY();
}

double Vector::GetCrossProduct(Vector firstVector) {
    return GetDX() * firstVector.GetDY() - GetDY() * firstVector.GetDX();
}

double Vector::ShortestRotationTo(Vector target) {
    double counterClockwiseMove = GetCompassDegrees() - target.GetCompassDegrees();
    double clockwiseMove = target.GetCompassDegrees() - GetCompassDegrees();
    clockwiseMove += (clockwiseMove < 0 ? 360 : 0);
    counterClockwiseMove += (counterClockwiseMove < 0 ? 360 : 0);
    return (abs(clockwiseMove) < abs(counterClockwiseMove) ? clockwiseMove : -counterClockwiseMove);
}

void Vector::SetMagnitude(double magnitude) {
    m_r = magnitude;
}
double Vector::GetCos() {
    return cos(m_theta);
}
double Vector::GetSin() {
    return sin(m_theta);
}
