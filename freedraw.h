#ifndef FREEDRAW_H
#define FREEDRAW_H

#include "shape.h"

class FreeDraw : public Shape
{
public:
    FreeDraw();

    void draw(QPainter* painter) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

    bool clickedIn(QMouseEvent *event);
    bool isClickedOn(QMouseEvent *event) override;
    void translate(Vec2d translateBy) override;

private:
    QPainterPath path;
};

#endif // FREEDRAW_H
