#ifndef SHAPE_H
#define SHAPE_H

#include <QPainter>
#include <QMouseEvent>
#include <memory>
#include "vec2dfuncs.h"

enum class State { Precreated, Creating, Moving, Finished };

class Shape;
typedef std::vector<std::unique_ptr<Shape>> ShapePtrVctr;

class Shape
{
public:
    Shape();

    virtual ~Shape() = 0;

    virtual void draw(QPainter *painter) = 0;
    virtual void drawOffset(QPainter *painter, Vec2d offset) = 0;
    virtual void mousePressEvent(QMouseEvent *event) = 0;
    virtual void mouseMoveEvent(QMouseEvent *event) = 0;
    virtual void mouseReleaseEvent(QMouseEvent *);
    virtual void translate(Vec2d translateBy) = 0;
    virtual void changePen(QPen pen) {this->pen = pen;}
    virtual void changeBrush(QBrush brush) {this->brush = brush;}
    virtual bool isClickedOn(QMouseEvent *event) = 0;
    virtual std::vector<Vec2d> boundingRect() = 0;
    virtual void fixOffscreen() = 0;
    virtual void normalize(int scale) = 0;
    virtual ShapePtrVctr disband() = 0;

    State currentState = State::Precreated;
    Vec2d movePoint;
    double  theta = M_PI / 4; //currently unused

    unsigned int index;

    QPen pen;
    QBrush brush;
};

#endif // SHAPE_H
