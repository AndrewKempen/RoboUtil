#include "Math/Point_OLD.h"

Point_OLD::Point_OLD() {
    m_x = 0;
    m_y = 0;
}

Point_OLD::Point_OLD(double x, double y) {
    m_x = x;
    m_y = y;
}

double Point_OLD::hypotenuse() {
    return hypot(m_x, m_y);
}

double Point_OLD::getX() {
    return m_x;
}

double Point_OLD::getY() {
    return m_y;
}

void Point_OLD::setX(double x) {
    m_x = x;
}

void Point_OLD::setY(double y) {
    m_y = y;
}

void Point_OLD::transformBy(Vector vector) {
    m_x += vector.GetDX();
    m_y += vector.GetDY();
}

void Point_OLD::rotateBy(Angle angle) {
    m_x = m_x * angle.getCos() - m_y * angle.getSin();
    m_y = m_x * angle.getSin() + m_y * angle.getCos();
}

void Point_OLD::flipOverOrigin() {
    m_x = -m_x;
    m_y = -m_y;
}

void Point_OLD::flipOverYAxis() {
    m_x = -m_x;
}

void Point_OLD::flipOverXAxis() {
    m_y = -m_y;
}

double Point_OLD::getSin() {
    return m_x / hypotenuse();
}

double Point_OLD::getCos() {
    return m_y / hypotenuse();
}

void Point_OLD::setXY(double x, double y) {
    setX(x);
    setY(y);
}

Point_OLD Point_OLD::operator+(Point_OLD other) {
    return Point_OLD(m_x + other.getX(), m_y + other.getY());
}

Point_OLD Point_OLD::operator-(Point_OLD other) {
    return Point_OLD(m_x - other.getX(), m_y - other.getY());
}