#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "shape.h"
#include "vec2d.h"
#include <QPainter>

class Ellipse : public Shape
{
public:
    void draw(QPainter* painter) override;
    Ellipse(Vec2d p1, Vec2d p2);
    Ellipse(Vec2d p1, int w, int h);

private:
    Vec2d p1;
    int w;
    int h;
};

#endif // ELLIPSE_H
