#ifndef SHAPE_H
#define SHAPE_H

#include <QPainter>
#include <QMouseEvent>
#include <memory>
#include "vec2dfuncs.h"

#define EX event->localPos().x()
#define EY event->localPos().y()

enum class State { Precreated, Creating, Moving, Finished };

class Shape;
typedef std::vector<std::unique_ptr<Shape>> ShapePtrVctr;

class Shape
{
public:
    Shape();

    virtual ~Shape() = 0;

    virtual void draw(QPainter *painter) = 0;
    virtual void draw(QPainter *painter, Vec2d offset) = 0;
    virtual void mousePressEvent(QMouseEvent *event) = 0;
    virtual void mouseMoveEvent(QMouseEvent *event) = 0;
    virtual void mouseReleaseEvent(QMouseEvent *);
    virtual void translate(Vec2d translateBy) = 0;
    virtual bool isClickedOn(QMouseEvent *event) = 0;
    virtual Vec2d boundingRect() = 0;
    virtual ShapePtrVctr disband() = 0;
    virtual void tile() = 0;
    virtual void changePen(QPen pen) {this->pen = pen;}
    virtual void changeBrush(QBrush brush) {this->brush = brush;}

    State currentState = State::Precreated;
    Vec2d movePoint;
    unsigned int index;
    QPen pen;
    QBrush brush;
};

#endif // SHAPE_H
