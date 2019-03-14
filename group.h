#ifndef GROUP_H
#define GROUP_H

#include "shape.h"
#include <vector>
#include <memory>

class Group : public Shape
{
public:
    Group();

    void draw(QPainter* painter) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

    bool isClickedOn(QMouseEvent *event) override;

    void translate(Vec2d translateBy) override;

    std::vector<std::unique_ptr<Shape>> childShapes;
};

#endif // GROUP_H
