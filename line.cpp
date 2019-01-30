#include "line.h"

Line::Line() {

}

Line::Line(Vec2d p1, Vec2d p2)
{
    this->p1 = p1;
    this->p2 = p2;
}

void Line::draw(QPainter *painter) {
    painter->setPen(selfPen);
    painter->drawLine(p1.x(), p1.y(), p2.x(), p2.y());
}

void Line::mousePressEvent(QMouseEvent *event) {
    p1 = {event->x(), event->y()};
    p2 = {event->x(), event->y()};
}

void Line::mouseMoveEvent(QMouseEvent *event) {
    p2 = {event->x(), event->y()};
}

void Line::mouseReleaseEvent(QMouseEvent *event) {

}
