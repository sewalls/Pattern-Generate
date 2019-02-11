#include "ellipse.h"

Ellipse::Ellipse() {

}

Ellipse::Ellipse(Vec2d p1, Vec2d p2) {
    this->p1 = p1;
    this->p2 = p2;
}

Ellipse::Ellipse(Vec2d p1, double w, double h) {
    this->p1 = p1;
    p2 = {p1.x + w, p1.y + h};
}

void Ellipse::draw(QPainter* painter) {
    painter->setPen(selfPen);
    painter->drawEllipse(QRectF{p1.x, p1.y, p2.x, p2.y});
}

void Ellipse::mousePressEvent(QMouseEvent *event) {
    p1 = {event->localPos().x(), event->localPos().y()};
    p2 = {event->localPos().x() - p1.x, event->localPos().y() - p1.y};
}

void Ellipse::mouseMoveEvent(QMouseEvent *event) {
    p2 = {event->localPos().x() - p1.x, event->localPos().y() - p1.y};
}

void Ellipse::mouseReleaseEvent(QMouseEvent *event) {

}

void Ellipse::mousePressEventSelect(QMouseEvent *event) {

}

void Ellipse::mouseMoveEventSelect(QMouseEvent *event) {

}

void Ellipse::mouseReleaseEventSelect(QMouseEvent *event) {

}

double Ellipse::distanceClicked(QMouseEvent *event) {

}
