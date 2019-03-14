#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "shape.h"

class Rectangle : public Shape
{
public:
    Rectangle();
    Rectangle(Vec2d p1, Vec2d p2);
    Rectangle(Vec2d p1, double w, double h);

    void draw(QPainter* painter) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

    bool isClickedOn(QMouseEvent *event) override;
    void translate(Vec2d translateBy) override;

    double width();
    double height();

private:
    Vec2d p1;
    Vec2d p2;
};

#endif // RECTANGLE_H
