#ifndef GROUP_H
#define GROUP_H

#include "shape.h"

class Group : public Shape
{
public:
    Group();

    void draw(QPainter *painter) override;
    void drawOffset(QPainter *painter, Vec2d offset) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void translate(Vec2d translateBy) override;
    void tile();
    bool isClickedOn(QMouseEvent *event) override;
    std::vector<Vec2d> boundingRect() override;
    void fixOffscreen() override;
    void normalize(int scale) override;
    ShapePtrVctr disband() override;

    ShapePtrVctr childShapes;
    bool isTiling = false;
};

#endif // GROUP_H
