#include "rectangle.h"

Rectangle::Rectangle()
{

}

void Rectangle::draw(QPainter *painter) {
    QPainterPath path;
    path.moveTo({p1.x, p1.y});
    path.lineTo({dp1.x, dp1.y});
    path.lineTo({p2.x, p2.y});
    path.lineTo({dp2.x, dp2.y});
    path.lineTo({p1.x, p1.y});
    brush.setStyle(Qt::SolidPattern);
    painter->setPen(pen);
    painter->setBrush(brush);
    painter->drawPath(path);
}

void Rectangle::mousePressEvent(QMouseEvent *event) {
    switch(currentState) {
    case State::Precreated:
        p1 = {event->localPos().x(), event->localPos().y()};
        p2 = {event->localPos().x(), event->localPos().y()};
        currentState = State::Creating;
        break;
    case State::Creating:
        currentState = State::Finished;
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

void Rectangle::mouseMoveEvent(QMouseEvent *event) {
    switch(currentState) {
    case State::Creating:
        p2 = {event->localPos().x(), event->localPos().y()};
        dp1 = {p2.x, p1.y};
        dp2 = {p1.x, p2.y};
        break;
    case State::Moving:
        translate({event->localPos().x() - movePoint.x, event->localPos().y() - movePoint.y});
        movePoint = {event->localPos().x(), event->localPos().y()};
        break;
    default:
        break;
    }
}

bool Rectangle::isClickedOn(QMouseEvent *event) {
    if((event->localPos().x() > p2.x && event->localPos().x() < p1.x) || (event->localPos().x() > p1.x && event->localPos().x() < p2.x)) {
        if((event->localPos().y() > p2.y && event->localPos().y() < p1.y) || (event->localPos().y() > p1.y && event->localPos().y() < p2.y)) {
            return true;
        }
    }
    return false;
}

void Rectangle::translate(Vec2d translateBy) {
    p1.translate(translateBy.x, translateBy.y);
    p2.translate(translateBy.x, translateBy.y);
    dp1 = {p2.x, p1.y};
    dp2 = {p1.x, p2.y};
}

void Rectangle::rotate(double theta) {
    Vec2d center = {(p1.x + p2.x) / 2, (p1.y + p2.y) / 2};
    p1.rotate(center, theta);
    dp1.rotate(center, theta);
    p2.rotate(center, theta);
    dp2.rotate(center, theta);
}
