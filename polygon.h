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
    void rotate(double theta) override;
    void translate(Vec2d translateBy) override;
    bool isClickedOn(QMouseEvent *event) override;

private:
    QPainterPath path;
};

#endif // POLYGON_H
