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
    bool isClickedOn(QMouseEvent *event) override;
    void fixOffscreen() override;
    virtual Rectangle* clone_impl() const override { return new Rectangle(*this); }
    ShapePtrVctr disband() override;

//private:
    Vec2d p1;
    Vec2d p2;
};

#endif // RECTANGLE_H
