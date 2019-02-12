#include "rectangle.h"

Rectangle::Rectangle() {

}

Rectangle::Rectangle(Vec2d p1, Vec2d p2)
{
    this->p1 = p1;
    this->p2 = p2;
}

Rectangle::Rectangle(Vec2d p1, double w, double h) {
    this->p1 = p1;
    p2 = {p1.x - w, p1.y - h};
}

double Rectangle::width() {
    return p2.x - p1.x;
}

double Rectangle::height() {
    return p2.y - p1.y;
}

void Rectangle::draw(QPainter* painter) {
    painter->setPen(selfPen);
    painter->drawRect(QRectF{p1.x, p1.y, width(), height()}); // is this resource inefficient?
}

void Rectangle::mousePressEvent(QMouseEvent *event) {
    p1 = {event->localPos().x(), event->localPos().y()};
    p1 = {event->localPos().x(), event->localPos().y()};
}

void Rectangle::mouseMoveEvent(QMouseEvent *event) {
    p2 = {event->localPos().x(), event->localPos().y()};
}

void Rectangle::mouseReleaseEvent(QMouseEvent *event) {
    p2 = {event->localPos().x(), event->localPos().y()};
}

void Rectangle::mousePressEventSelect(QMouseEvent *event) {
    if((event->localPos().x() > p2.x && event->localPos().x() < p1.x) || (event->localPos().x() > p1.x && event->localPos().x() < p2.x)) {
        if((event->localPos().y() > p2.y && event->localPos().y() < p1.y) || (event->localPos().y() > p1.y && event->localPos().y() < p2.y)) {
            isMoving = true;
            movePoint = {event->localPos().x(), event->localPos().y()};
        }
    }
}

void Rectangle::mouseMoveEventSelect(QMouseEvent *event) {
    if(isMoving) {
        p1.translate(event->localPos().x() - movePoint.x, event->localPos().y() - movePoint.y);
        p2.translate(event->localPos().x() - movePoint.x, event->localPos().y() - movePoint.y);
        movePoint = {event->localPos().x(), event->localPos().y()};
    }
}

void Rectangle::mouseReleaseEventSelect(QMouseEvent *event) {
    isMoving = false;
}
