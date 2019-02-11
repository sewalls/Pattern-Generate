#ifndef FREEDRAW_H
#define FREEDRAW_H

#include "shape.h"
#include "vec2d.h"
#include <QPainter>
#include <QMouseEvent> //why do I need to reinclude this?

class FreeDraw : public Shape  //todo: freedraw line type change
{
public:
    void draw(QPainter* painter) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    double distanceClicked(QMouseEvent *event) override;

    void mouseMoveEventSelect(QMouseEvent *event) override;
    void mousePressEventSelect(QMouseEvent *event) override;
    void mouseReleaseEventSelect(QMouseEvent * event) override;

    bool clickedIn(QMouseEvent *event);

    FreeDraw();

private:
    QPainterPath path;

    double negDotProduct(Vec2d p1, Vec2d p2);
    double whichSide(Vec2d p1, Vec2d p2, Vec2d q1);
    bool lineSegsIntersect(Vec2d p1, Vec2d p2, Vec2d q1, Vec2d q2);

};

#endif // FREEDRAW_H
