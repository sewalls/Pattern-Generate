#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "shape.h"
#include "vec2d.h"
#include <QPainter>

class Rectangle : public Shape
{
public:
    Rectangle();
    Rectangle(Vec2d p1, Vec2d p2);
    void draw(QPainter* painter) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    int width();
    int height();

private:
    Vec2d p1;
    Vec2d p2;
};

#endif // RECTANGLE_H
