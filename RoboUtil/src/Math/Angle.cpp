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

/**
 * Return an angle based from given degrees
 * @param degrees
 * @return
 */
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

/**
 * Rotate this angle by another angle and return the result
 *
 * Does not modify either angle
 *
 * @param other
 * @return Addition of this angle and the other angle
 */

Angle Angle::getRotateBy(Angle other) {
	return Angle(m_cos * other.getCos() - m_sin * other.getSin(),
			m_cos * other.getSin() + m_sin * other.getCos(), true);
}

/**
 * Get the inverse of this angle. The inverse of this angle is the angle such that X + Y = 0, where X is this angle and
 * Y is the returned angle
 * @return
 */

Angle Angle::getInverse() {
	return Angle(m_cos, -m_sin, false);
}

/**
 * Get the angle opposite to this angle. The opposite of this angle is the angle opposite to this angle on the unit
 * circle
 * @return
 */
Angle Angle::getOpposite() {
	return Angle(-m_cos, -m_sin, false);
}

Angle Angle::interpolate(Angle other, double x) {
	if (x <= 0){
		return *this;
	} else if (x >= 1){
		return other;
	}
	double diff = getInverse().getRotateBy(other).getRadians();
	return getRotateBy(fromRadians(diff * x));
}

void Angle::setDegrees(double degrees) {
    setRadians(toRadians(degrees));
}

void Angle::setRadians(double radians) {
    m_cos = cos(radians);
    m_sin = sin(radians);
}
