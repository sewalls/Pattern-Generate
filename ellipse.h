#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "shape.h"

class Ellipse : public Shape
{
public:
    Ellipse();
    Ellipse(Vec2d p1, Vec2d p2);
    Ellipse(Vec2d p1, double w, double h);

    void draw(QPainter* painter) override;
    void drawSelected(QPainter* painter) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

    bool isClickedOn(QMouseEvent *event) override;

    std::vector<Vec2d> param();

private:
    Vec2d p1;
    Vec2d p2;
};

#endif // ELLIPSE_H
