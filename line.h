#ifndef LINE_H
#define LINE_H

#include "shape.h"

class Line : public Shape
{
public:
    Line();

    void draw(QPainter *painter) override;
    void drawOffset(QPainter *painter, Vec2d offset) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void translate(Vec2d translateBy) override;
    bool isClickedOn(QMouseEvent *event) override;
    std::vector<Vec2d> boundingRect() override;
    void fixOffscreen() override;
    void normalize(int scale) override;
    ShapePtrVctr disband() override;

private:
    Vec2d p1;
    Vec2d p2;
};

#endif // LINE_H
