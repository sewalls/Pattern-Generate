#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "shape.h"
#include "vec2d.h"
#include <QPainter>
#include <QMouseEvent> //why do I need to reinclude this?

class Ellipse : public Shape
{
public:
    Ellipse();
    Ellipse(Vec2d p1, Vec2d p2);
    Ellipse(Vec2d p1, double w, double h);

    void draw(QPainter* painter) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

    void mouseMoveEventSelect(QMouseEvent *event) override;
    void mousePressEventSelect(QMouseEvent *event) override;
    void mouseReleaseEventSelect(QMouseEvent * event) override;

    double distanceClicked(QMouseEvent *event);

private:
    Vec2d p1;
    Vec2d p2;
};

#endif // ELLIPSE_H
