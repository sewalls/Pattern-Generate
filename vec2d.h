#ifndef VEC2D_H
#define VEC2D_H

#include <math.h>

class Vec2d
{
public:
    Vec2d();
    Vec2d(double x, double y);

    void translate(double x, double y);
    void rotate(Vec2d center, double theta);

    Vec2d scaled(double s) {return {x * s, y * s};}

    double lengthSquared() {return x * x + y * y;}

    double x;
    double y;
};

double operator*(Vec2d p1, Vec2d p2);
Vec2d operator+(Vec2d p1, Vec2d p2);
Vec2d operator-(Vec2d p1, Vec2d p2);

#endif // VEC2D_H
