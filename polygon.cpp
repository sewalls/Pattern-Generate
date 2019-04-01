#include "Polygon.h"

Polygon::Polygon()
{

}

void Polygon::draw(QPainter *painter) {
    brush.setStyle(Qt::SolidPattern);
    painter->setPen(pen);
    painter->setBrush(brush);
    painter->drawPath(path);
    painter->fillPath(path, brush);
}

void Polygon::mousePressEvent(QMouseEvent *event) {
    switch(currentState) {
    case State::Precreated:
        path.moveTo(event->localPos().x(), event->localPos().y());
        currentState = State::Creating;
        break;
    case State::Creating:
        if(std::abs(event->localPos().x() - path.elementAt(0).x) < 5 ||
                std::abs(event->localPos().y() - path.elementAt(0).y) < 5) {
            path.closeSubpath();
            currentState = State::Finished;
        }
        else {
            path.lineTo(event->localPos().x(), event->localPos().y());
        }
        break;
    case State::Moving:
        if(isClickedOn(event)) {
            movePoint = {event->localPos().x(), event->localPos().y()};
        }
        else {
            currentState = State::Finished;
        }
        break;
    default:
        break;
    }
}

void Polygon::mouseMoveEvent(QMouseEvent *event) {
    switch(currentState) {
    case State::Creating:
        break;
    case State::Moving: {
        translate({event->localPos().x() - movePoint.x, event->localPos().y() - movePoint.y});
        movePoint = {event->localPos().x(), event->localPos().y()};
        break;
    }
    default:
        break;
    }
}

void Polygon::mouseReleaseEvent(QMouseEvent *) {
    if(currentState == State::Moving) {
        currentState = State::Finished;
    }
}

bool Polygon::isClickedOn(QMouseEvent *event) {
    Vec2d u = {event->localPos().x(), event->localPos().y()};
    Vec2d v = {event->localPos().x() + 10000, event->localPos().y()};

    int count = 0;

    if(lineSegsIntersect(u, v, {path.currentPosition().x(), path.currentPosition().y()}, {path.elementAt(0).x, path.elementAt(0).y})) {
        count++;
    }

    for(int i = 0; i < path.elementCount() - 1; i++) {
        if(lineSegsIntersect(u, v, {path.elementAt(i).x, path.elementAt(i).y}, {path.elementAt(i+1).x, path.elementAt(i+1).y})) {
            count++;
        }
    }

    return count % 2;
}

void Polygon::translate(Vec2d translateBy) {
    path.translate(translateBy.x, translateBy.y);
}
