#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "shape.h"

class Rectangle : public Shape
{
public:
    Rectangle();

    void draw(QPainter *painter) override;
    void draw(QPainter *painter, Vec2d offset) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void translate(Vec2d translateBy) override;
    bool isClickedOn(QMouseEvent *event) override;
    Vec2d boundingRect() override;
    ShapePtrVctr disband() override {return ShapePtrVctr{};}
    void tile() override {}

    Vec2d p1;
    Vec2d p2;
};

#endif // RECTANGLE_H
