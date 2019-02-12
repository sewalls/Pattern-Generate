#include "vec2d.h"

Vec2d::Vec2d()
{
    x = 0;
    y = 0;
}

Vec2d::Vec2d(double x, double y) {
    this->x = x;
    this->y = y;
}

void Vec2d::translate(double x, double y) {
    this->x += x;
    this->y += y;
}

double operator*(Vec2d p1, Vec2d p2) {
    return double {p1.x * p2.x + p1.y * p2.y};
}

Vec2d operator-(Vec2d p1, Vec2d p2)
{
    return Vec2d {p1.x - p2.x, p1.y - p2.y};
}

Vec2d operator+(Vec2d p1, Vec2d p2)
{
    return Vec2d {p1.x + p2.x, p1.y + p2.y};
}
