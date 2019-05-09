#include "vec2dfuncs.h"

double dotProduct(Vec2d p1, Vec2d p2) {
    return p1.x * p2.x + p1.y * p2.y;
}

double negDotProduct(Vec2d p1, Vec2d p2) {
    return p1.x * p2.x - p1.y * p2.y;
}

double whichSide(Vec2d p1, Vec2d p2, Vec2d q1) {
    Vec2d a = {p2.y - p1.y, p2.x - p1.x};
    Vec2d b = {q1.x - p1.x, q1.y - p1.y};

    return negDotProduct(a, b);
}

bool lineSegsIntersect(Vec2d p1, Vec2d p2, Vec2d q1, Vec2d q2) {
    return ((whichSide(p1, p2, q1) * (whichSide(p1, p2, q2)) < 0) && ((whichSide(q1, q2, p1)) * (whichSide(q1, q2, p2)) < 0));
}

double distanceBetween(Vec2d p1, Vec2d p2) {
    return sqrt(pow((p2.x - p1.x), 2) + pow((p2.y - p1.y), 2));
}

Vec2d projection(Vec2d p1, Vec2d p2) {
    Vec2d unit = p1.unit();
    return unit.scaled(dotProduct(p1, p2));
}
