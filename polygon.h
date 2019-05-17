#ifndef POLYGON_H
#define POLYGON_H

#include "shape.h"

class Polygon : public Shape
{
public:
    Polygon();

    void draw(QPainter *painter) override;
    void draw(QPainter *painter, Vec2d offset) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void translate(Vec2d translateBy) override;
    bool isClickedOn(QMouseEvent *event) override;
    Vec2d boundingRect() override;
    ShapePtrVctr disband() override;
    void tile() override {}
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    QPainterPath path;
};

#endif // POLYGON_H
