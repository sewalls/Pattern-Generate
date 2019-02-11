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

    void mouseMoveEventSelect(QMouseEvent *event) override;
    void mousePressEventSelect(QMouseEvent *event) override;
    void mouseReleaseEventSelect(QMouseEvent * event) override;

    double distanceClicked(QMouseEvent *event);

protected:
    Vec2d p1;
    Vec2d p2;
};

#endif // LINE_H
