#ifndef LINE_H
#define LINE_H

#include "shape.h"

class Line : public Shape
{
public:
    Line();
    Line(Vec2d p1, Vec2d p2);

    void draw(QPainter* painter) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

    double distanceClicked(QMouseEvent *event);
    bool isClickedOn(QMouseEvent *event) override;

protected:
    Vec2d p1;
    Vec2d p2;
};

#endif // LINE_H
