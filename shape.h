#ifndef SHAPE_H
#define SHAPE_H

#include <QMouseEvent>
#include <QPen>
#include <vec2d.h>

class QPainter;

class Shape  //todo: add triangle class, use painter path, should be easy
{
public:
    Shape();

    virtual void draw(QPainter* painter) = 0;
    virtual void mousePressEvent(QMouseEvent *event) = 0;
    virtual void mouseMoveEvent(QMouseEvent *event) = 0;
    virtual void mouseReleaseEvent(QMouseEvent *event) = 0;

    virtual void mousePressEventSelect(QMouseEvent *event) = 0;
    virtual void mouseMoveEventSelect(QMouseEvent *event) = 0;
    virtual void mouseReleaseEventSelect(QMouseEvent * event) = 0;

    virtual void changePen(QPen pen) {this->pen = pen;}

    bool isMoving = false;

protected:
    QPen pen;
    Vec2d movePoint;
};

#endif // SHAPE_H
