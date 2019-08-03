#pragma once

#include "Angle.h"
#include "Vector.h"

class Point_OLD{
protected:
	double m_x, m_y;

public:
	Point_OLD();

	Point_OLD(double x, double y);

	double hypotenuse();

	double getX();

	double getY();

	void setX(double x);

	void setY(double y);

	void setXY(double x, double y);

	void transformBy(Vector vector);

	void rotateBy(Angle angle);

    void flipOverOrigin();

    void interpolate(Point_OLD other, double x);

    void extrapolate(Point_OLD other, double x);

    void flipOverYAxis();
    void flipOverXAxis();

	double getSin();
	double getCos();

    Point_OLD operator+(Point_OLD other);
    Point_OLD operator-(Point_OLD other);

};
