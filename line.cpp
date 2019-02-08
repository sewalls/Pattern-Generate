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
    painter->drawLine(QLineF{p1.x, p1.y, p2.x, p2.y});
}

void Line::mousePressEvent(QMouseEvent *event) {
    p1 = {event->localPos().x(), event->localPos().y()};
    p2 = {event->localPos().x(), event->localPos().y()};
}

void Line::mouseMoveEvent(QMouseEvent *event) {
    p2 = {event->localPos().x(), event->localPos().y()};
}

void Line::mouseReleaseEvent(QMouseEvent *event) {

}

void Line::mousePressEventSelect(QMouseEvent *event) {

}

void Line::mouseMoveEventSelect(QMouseEvent *event) {

}

double Line::distanceClicked(QMouseEvent *event) {

}
