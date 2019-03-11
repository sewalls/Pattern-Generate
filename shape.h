#ifndef SHAPE_H
#define SHAPE_H

#include <QMouseEvent>
#include <QPainter>
#include <vec2d.h>

enum State { Precreated, Creating, Moving, Finished }; //change name potentially

class QPainter;

class Shape
{
public:
    Shape();
    virtual ~Shape() = 0;

    virtual void draw(QPainter* painter) = 0;
    virtual void drawSelected(QPainter* painter) = 0;
    virtual void mousePressEvent(QMouseEvent *event) = 0;
    virtual void mouseMoveEvent(QMouseEvent *event) = 0;
    virtual void mouseReleaseEvent(QMouseEvent *event) = 0;

    virtual void changePen(QPen pen) {this->pen = pen;}
    virtual void changeBrush(QBrush brush) {this->brush = brush;}
    virtual bool isClickedOn(QMouseEvent *event) = 0;

    bool isMoving = false;
    State currentState = Precreated;

//protected:
    QPen pen;
    QBrush brush;
    Vec2d movePoint;
};

#endif // SHAPE_H
