#ifndef LINE_H
#define LINE_H

#include "shape.h"

class Line : public Shape
{
public:
    Line();

    void draw(QPainter *painter) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void translate(Vec2d translateBy) override;
    bool isClickedOn(QMouseEvent *event) override;
    void fixOffscreen() override;
    virtual Line* clone_impl() const override { return new Line(*this); }
    ShapePtrVctr disband() override;

private:
    Vec2d p1;
    Vec2d p2;
};

#endif // LINE_H
