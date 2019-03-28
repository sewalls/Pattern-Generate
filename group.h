#ifndef GROUP_H
#define GROUP_H

#include "shape.h"

class Group : public Shape
{
public:
    Group();

    void draw(QPainter *painter) override;
    void drawTiled(QPainter *painter);
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void rotate(double theta) override;
    void translate(Vec2d translateBy) override;
    bool isClickedOn(QMouseEvent *event) override;

    ShapePtrVctr childShapes;
};

#endif // GROUP_H
