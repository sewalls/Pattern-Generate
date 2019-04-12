#ifndef GROUP_H
#define GROUP_H

#include "shape.h"

class Group : public Shape
{
public:
    Group();

    void draw(QPainter *painter) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void translate(Vec2d translateBy) override;
    void tile();
    bool isClickedOn(QMouseEvent *event) override;
    void fixOffscreen() override;
    virtual Group* clone_impl() const override;
    ShapePtrVctr disband() override;

    ShapePtrVctr childShapes;
};

#endif // GROUP_H
