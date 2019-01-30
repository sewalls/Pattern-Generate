#include "freedraw.h"

FreeDraw::FreeDraw()
{

}

void FreeDraw::draw(QPainter* painter) {
    painter->drawPath(path);
}

void FreeDraw::mousePressEvent(QMouseEvent *event) {
    path.moveTo(event->x(), event->y());
}

void FreeDraw::mouseMoveEvent(QMouseEvent *event) {
    path.lineTo(event->x(), event->y());
}

void FreeDraw::mouseReleaseEvent(QMouseEvent *event) {

}
