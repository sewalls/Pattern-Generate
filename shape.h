#ifndef SHAPE_H
#define SHAPE_H

#include <QPainter>
#include <QMouseEvent>
#include <memory>
#include "vec2dfuncs.h"

enum class State { Precreated, Creating, Moving, Finished };

class Shape
{
public:
    Shape();
    virtual ~Shape() = 0;

    virtual void draw(QPainter *painter) = 0;
    virtual void mousePressEvent(QMouseEvent *event) = 0;
    virtual void mouseMoveEvent(QMouseEvent *event) = 0;
    virtual void mouseReleaseEvent(QMouseEvent *);
    virtual void translate(Vec2d translateBy) = 0;
    virtual void rotate(double theta) = 0;
    virtual void changePen(QPen pen) {this->pen = pen;}
    virtual void changeBrush(QBrush brush) {this->brush = brush;}
    virtual bool isClickedOn(QMouseEvent *event) = 0;

    State currentState = State::Precreated;
    Vec2d movePoint;

    unsigned int index;

    QPen pen;
    QBrush brush;
};

typedef std::vector<std::unique_ptr<Shape>> ShapePtrVctr;

#endif // SHAPE_H
