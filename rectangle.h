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
    Rectangle(Vec2d p1, double w, double h);
    void draw(QPainter* painter) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

    void mouseMoveEventSelect(QMouseEvent *event) override;
    void mousePressEventSelect(QMouseEvent *event) override;
    void mouseReleaseEventSelect(QMouseEvent * event) override;

    double distanceClicked(QMouseEvent *event) override;

    double width();
    double height();

private:
    Vec2d p1;
    Vec2d p2;
};

#endif // RECTANGLE_H
