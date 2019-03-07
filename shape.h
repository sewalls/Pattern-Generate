#ifndef SHAPE_H
#define SHAPE_H

#include <QMouseEvent>
#include <QPainter>
#include <QPen>
#include <vec2d.h>

enum State { Precreated, Creating, Moving, Finished }; //change name potentially

class QPainter;

class Shape
{
public:
    Shape();

    virtual void draw(QPainter* painter) = 0;
    virtual void drawSelected(QPainter* painter) = 0;
    virtual void mousePressEvent(QMouseEvent *event) = 0;
    virtual void mouseMoveEvent(QMouseEvent *event) = 0;
    virtual void mouseReleaseEvent(QMouseEvent *event) = 0;

    virtual void changePen(QPen pen) {this->pen = pen;}
    virtual bool isClickedOn(QMouseEvent *event) = 0;

    bool isMoving = false;
    State currentState = Precreated;

protected:
    QPen pen;
    Vec2d movePoint;
};

#endif // SHAPE_H
