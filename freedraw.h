#ifndef FREEDRAW_H
#define FREEDRAW_H

#include "shape.h"
#include "vec2d.h"
#include <QPainter>
#include <QMouseEvent> //why do I need to reinclude this?

class FreeDraw : public Shape  //todo: freedraw line type change
{
public:
    void draw(QPainter* painter) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    FreeDraw();

private:
    QPainterPath path;
};

#endif // FREEDRAW_H
