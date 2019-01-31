#include "freedraw.h"

FreeDraw::FreeDraw()
{

}

void FreeDraw::draw(QPainter* painter) {
    painter->drawPath(path);
}

void FreeDraw::mousePressEvent(QMouseEvent *event) {
    path.moveTo(event->localPos().x(), event->localPos().y());
}

void FreeDraw::mouseMoveEvent(QMouseEvent *event) {
    path.lineTo(event->localPos().x(), event->localPos().y());
}

void FreeDraw::mouseReleaseEvent(QMouseEvent *event) {

}
