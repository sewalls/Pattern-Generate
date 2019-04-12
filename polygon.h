#ifndef POLYGON_H
#define POLYGON_H

#include "shape.h"

class Polygon : public Shape
{
public:
    Polygon();

    void draw(QPainter *painter) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void translate(Vec2d translateBy) override;
    bool isClickedOn(QMouseEvent *event) override;
    void fixOffscreen() override;
    virtual Polygon* clone_impl() const override { return new Polygon(*this); }
    ShapePtrVctr disband() override;

private:
    QPainterPath path;
};

#endif // POLYGON_H
