#ifndef VEC2DFUNCS_H
#define VEC2DFUNCS_H

#include "vec2d.h"

double NegDotProduct(Vec2d p1, Vec2d p2);
double whichSide(Vec2d p1, Vec2d p2, Vec2d q1);
bool lineSegsIntersect(Vec2d p1, Vec2d p2, Vec2d q1, Vec2d q2);

#endif // VEC2DFUNCS_H
