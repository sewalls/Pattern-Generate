#ifndef VEC2D_H
#define VEC2D_H

class Vec2d
{
public:
    Vec2d();
    Vec2d(double x, double y);

    double x;
    double y;
};

Vec2d operator+(Vec2d p1, Vec2d p2); //why declared out here?
Vec2d operator-(Vec2d p1, Vec2d p2);

#endif // VEC2D_H
