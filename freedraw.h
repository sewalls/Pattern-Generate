#ifndef FREEDRAW_H
#define FREEDRAW_H

#include "shape.h"

class FreeDraw : public Shape
{
public:
    FreeDraw();

    void draw(QPainter* painter) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

    void mouseMoveEventSelect(QMouseEvent *event) override;
    void mousePressEventSelect(QMouseEvent *event) override;
    void mouseReleaseEventSelect(QMouseEvent * event) override;

    bool clickedIn(QMouseEvent *event); //still not wholly accurate

private:
    QPainterPath path;

    double negDotProduct(Vec2d p1, Vec2d p2);
    double whichSide(Vec2d p1, Vec2d p2, Vec2d q1);
    bool lineSegsIntersect(Vec2d p1, Vec2d p2, Vec2d q1, Vec2d q2);
};

#endif // FREEDRAW_H
