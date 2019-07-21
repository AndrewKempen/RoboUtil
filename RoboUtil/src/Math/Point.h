#pragma once

#include "Angle.h"
#include "Vector.h"

class Point{
protected:
	double m_x, m_y;

public:
	Point();

	Point(double x, double y);

	double hypotenuse();

	double getX();

	double getY();

	void setX(double x);

	void setY(double y);

	void setXY(double x, double y);

	void transformBy(Vector vector);

	void rotateBy(Angle angle);

    void flipOverOrigin();

    void interpolate(Point other, double x);

    void extrapolate(Point other, double x);

    void flipOverYAxis();
    void flipOverXAxis();

	double getSin();
	double getCos();
};
