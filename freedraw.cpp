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
    if((std::abs((event->localPos().x() - path.currentPosition().x())) > 0.1)
        || (std::abs((event->localPos().y() - path.currentPosition().y())) > 0.1)) {
        path.lineTo(event->localPos().x(), event->localPos().y());
    }
}

void FreeDraw::mouseReleaseEvent(QMouseEvent *event) {

}
