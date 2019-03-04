#ifndef POLYLINE_H
#define POLYLINE_H

#include "shape.h"

class PolyLine : public Shape
{
public:
    PolyLine();

    void draw(QPainter* painter) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

    bool isClickedOn(QMouseEvent *event) override;

protected:
    QPainterPath path;

    double negDotProduct(Vec2d p1, Vec2d p2);
    double whichSide(Vec2d p1, Vec2d p2, Vec2d q1);
    bool lineSegsIntersect(Vec2d p1, Vec2d p2, Vec2d q1, Vec2d q2);
};

#endif // POLYLINE_H
