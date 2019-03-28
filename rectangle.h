#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "shape.h"

class Rectangle : public Shape
{
public:
    Rectangle();

    void draw(QPainter *painter) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void translate(Vec2d translateBy) override;
    void rotate(double theta) override;
    bool isClickedOn(QMouseEvent *event) override;

private:
    Vec2d p1;
    Vec2d p2;

    Vec2d dp1;
    Vec2d dp2;
};

#endif // RECTANGLE_H
