#ifndef SHAPE_H
#define SHAPE_H

#include <QMouseEvent>

class QPainter;

class Shape
{
public:
    Shape();
    virtual void draw(QPainter* painter) = 0;
    virtual void mousePressEvent(QMouseEvent *event) = 0;
    virtual void mouseMoveEvent(QMouseEvent *event) = 0;
    virtual void mouseReleaseEvent(QMouseEvent *event) = 0;

    virtual void changePen(Qt::PenStyle penType) {selfPen = penType;}

protected:
    Qt::PenStyle selfPen = Qt::SolidLine;
};

#endif // SHAPE_H
