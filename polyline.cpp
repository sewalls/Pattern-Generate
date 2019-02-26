#include "polyline.h"

PolyLine::PolyLine()
{

}

void PolyLine::draw(QPainter* painter) {
    painter->setPen(pen);
    painter->drawPath(path);
}

void PolyLine::mousePressEvent(QMouseEvent *event) {
    path.moveTo(event->localPos().x(), event->localPos().y());
}

void PolyLine::mouseMoveEvent(QMouseEvent *event) {

}

void PolyLine::mouseReleaseEvent(QMouseEvent *event) {

}

void PolyLine::mouseMoveEventSelect(QMouseEvent *event) {

}

void PolyLine::mousePressEventSelect(QMouseEvent *event) {

}

void PolyLine::mouseReleaseEventSelect(QMouseEvent * event) {

}
