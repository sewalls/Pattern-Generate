#ifndef POLYLINE_H
#define POLYLINE_H

#include "shape.h"

class PolyLine : public Shape
{
public:
    PolyLine();

    void draw(QPainter* painter) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

    void mouseMoveEventSelect(QMouseEvent *event) override;
    void mousePressEventSelect(QMouseEvent *event) override;
    void mouseReleaseEventSelect(QMouseEvent * event) override;

protected:
    QPainterPath path;
};

#endif // POLYLINE_H
