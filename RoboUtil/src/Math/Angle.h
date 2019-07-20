#pragma once

#include "Math.h"

class Angle{
protected:
	double m_cos, m_sin;

public:
	Angle();
	Angle(double x, double y, bool doNormalize);
	Angle(const Angle& other);

	static Angle fromRadians(double radians);
	static Angle fromDegrees(double degrees);

	void normalize();

	double getCos();
	double getSin();

	double getRadians();
	double getDegrees();

	Angle rotateBy(Angle other);
	Angle inverse();
	Angle opposite();

	Angle interpolate(Angle other, double x);
};
