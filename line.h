#ifndef LINE_H
#define LINE_H

#include "shape.h"
#include "vec2d.h"
#include <QPainter>

class Line : public Shape
{
public:
    Line();
    Line(Vec2d p1, Vec2d p2);
    void draw(QPainter* painter) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

protected:
    Vec2d p1;
    Vec2d p2;
};

#endif // LINE_H
