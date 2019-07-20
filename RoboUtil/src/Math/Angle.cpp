#include "Math/Angle.h"

Angle::Angle() {
	m_cos = 1;
	m_sin = 0;
}

Angle::Angle(double x, double y, bool doNormalize) {
	m_cos = x;
	m_sin = y;
	if(doNormalize){
		normalize();
	}
}

Angle::Angle(const Angle& other) {
	m_cos = other.m_cos;
	m_sin = other.m_sin;
}

Angle Angle::fromRadians(double radians) {
	return Angle(cos(radians), sin(radians), false);
}

Angle Angle::fromDegrees(double degrees) {
	return fromRadians(toRadians(degrees));
}

void Angle::normalize() {
	double mag = hypot(m_cos, m_sin);
	if (mag > kEpsilon){
		m_sin /= mag;
		m_cos /= mag;
	} else {
		m_sin = 0;
		m_cos = 1;
	}
}

double Angle::getCos() {
	return m_cos;
}

double Angle::getSin() {
	return m_sin;
}

double Angle::getRadians() {
	return atan2(m_sin, m_cos);
}

double Angle::getDegrees() {
	return toDegrees(getRadians());
}

Angle Angle::rotateBy(Angle other) {
	return Angle(m_cos * other.getCos() - m_sin * other.getSin(),
			m_cos * other.getSin() + m_sin * other.getCos(), true);
}

Angle Angle::inverse() {
	return Angle(m_cos, -m_sin, false);
}

Angle Angle::opposite() {
	return Angle(-m_cos, -m_sin, false);
}

Angle Angle::interpolate(Angle other, double x) {
	if (x <= 0){
		return *this;
	} else if (x >= 1){
		return other;
	}
	double diff = inverse().rotateBy(other).getRadians();
	return rotateBy(fromRadians(diff * x));
}
