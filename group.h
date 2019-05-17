#ifndef GROUP_H
#define GROUP_H

#include "shape.h"

class Group : public Shape
{
public:
    Group();

    void draw(QPainter *painter) override;
    void draw(QPainter *painter, Vec2d offset) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void translate(Vec2d translateBy) override;
    bool isClickedOn(QMouseEvent *event) override;
    Vec2d boundingRect() override;
    ShapePtrVctr disband() override;
    void tile() override;
    void changePen(QPen pen) override;
    void changeBrush(QBrush brush) override;

    ShapePtrVctr childShapes;
    bool isTiling = false;
};

#endif // GROUP_H
