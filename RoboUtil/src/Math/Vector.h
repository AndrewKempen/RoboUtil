#pragma once

#include "Math.h"

class Vector {
public:
	Vector();
	Vector(double r, double theta);
	Vector(const Vector& other);
    double GetCompassDegrees();
  	double GetDX();
  	double GetDY();
	static Vector FromCompassDegrees(double compassDegrees, double mag = 1);
	static Vector FromRadians(double radians, double mag = 1);
	static Vector FromDegrees(double degrees, double mag = 1);
	static Vector FromXY(double x, double y);
	Vector RotationInverse();
	Vector MagnitudeInverse();
	Vector Opposite();
	Vector FlipX();
	Vector FlipY();
	Vector RotateBy(Vector rotation);
	Vector InterpolateRotation(Vector other, double x);
	Vector InterpolateMagnitude(Vector other, double x);
	Vector TranslateBy(Vector other);
	Vector Extrapolate(Vector other, double x);
	double ShortestRotationTo(Vector target);
	void Normalize();
    double NormalizeMagnitude();
	void SetXY(double x, double y);
	void SetMagnitude(double magnitude);
    void Invert();
  	void AddVector(Vector firstVector);
	void SubtractVector(Vector firstVector);
  	double GetCrossProduct(Vector firstVector);
  	double GetDotProduct(Vector firstVector);
  	double GetMagnitude();
  	double GetDegrees();
  	double GetRadians();
  	double GetCos();
  	double GetSin();

protected:
  	double m_theta = 0;
    double m_r = 0;
};
