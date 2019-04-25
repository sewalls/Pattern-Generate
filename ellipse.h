#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "shape.h"

class Ellipse : public Shape
{
public:
    Ellipse();

    void draw(QPainter *painter) override;
    void drawOffset(QPainter *painter, Vec2d offset) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void translate(Vec2d translateBy) override;
    bool isClickedOn(QMouseEvent *event) override;
    std::vector<Vec2d> boundingRect() override;
    void fixOffscreen() override;
    void normalize() override;
    virtual Ellipse* clone_impl() const override { return new Ellipse(*this); }
    ShapePtrVctr disband() override;
    std::vector<Vec2d> param();

private:
    Vec2d p1;
    Vec2d p2;
};

#endif // ELLIPSE_H
