#include "Math/Point.h"

Point::Point() {
    m_x = 0;
    m_y = 0;
}

Point::Point(double x, double y) {
    m_x = x;
    m_y = y;
}

double Point::hypotenuse() {
    return hypot(m_x, m_y);
}

double Point::getX() {
    return m_x;
}

double Point::getY() {
    return m_y;
}

void Point::setX(double x) {
    m_x = x;
}

void Point::setY(double y) {
    m_y = y;
}

void Point::transformBy(Vector vector) {
    m_x += vector.GetDX();
    m_y += vector.GetDY();
}

void Point::rotateBy(Angle angle) {
    m_x = m_x * angle.getCos() - m_y * angle.getSin();
    m_y = m_x * angle.getSin() + m_y * angle.getCos();
}

void Point::flipOverOrigin() {
    m_x = -m_x;
    m_y = -m_y;
}

void Point::flipOverYAxis() {
    m_x = -m_x;
}

void Point::flipOverXAxis() {
    m_y = -m_y;
}

double Point::getSin() {
    return m_x / hypotenuse();
}

double Point::getCos() {
    return m_y / hypotenuse();
}

void Point::setXY(double x, double y) {
    setX(x);
    setY(y);
}
