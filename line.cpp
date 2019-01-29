#include "line.h"

Line::Line(Vec2d p1, Vec2d p2)
{
    this->p1 = p1;
    this->p2 = p2;
}

void Line::draw(QPainter *painter) {
    painter->drawLine(p1.x(), p1.y(), p2.x(), p2.y());
}
