#include "rectangle.h"

Rectangle::Rectangle()
{

}

void Rectangle::draw(QPainter *painter) {
    brush.setStyle(Qt::SolidPattern);
    painter->setPen(pen);
    painter->setBrush(brush);
    painter->drawRect(QRectF{p1.x, p1.y, p2.x - p1.x, p2.y - p1.y});
    //painter->drawRect(0, 0, boundingRect()[1].x, boundingRect()[1].y);
}

void Rectangle::drawOffset(QPainter *painter, Vec2d offset) {
    brush.setStyle(Qt::SolidPattern);
    painter->setPen(pen);
    painter->setBrush(brush);
    painter->drawRect(QRectF{p1.x + offset.x, p1.y + offset.y, p2.x - p1.x, p2.y - p1.y});
}

std::vector<Vec2d> Rectangle::boundingRect() {
    return {{std::min(p1.x, p2.x), std::min(p1.y, p2.y)}, {std::max(p1.x, p2.x), std::max(p1.y, p2.y)}};
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
}

void Rectangle::fixOffscreen() {
    if(std::min(p1.x, p2.x) > 1700) {
        translate({-1800, 0});
    }
    if(std::min(p1.y, p2.y) > 1000) {
        translate({0, -1100});
    }
    if(std::max(p1.x, p2.x) < -100) {
        translate({1800, 0});
    }
    if(std::max(p1.y, p2.y) < -100) {
        translate({0, 1100});
    }
}

void Rectangle::normalize() {
    Vec2d n1 = {std::min(p1.x, p2.x), std::min(p1.y, p2.y)};
    Vec2d n2 = {std::max(p1.x, p2.x), std::max(p1.y, p2.y)};
    p1 = n1;
    p2 = n2;

    double width = p2.x - p1.x;
    double height = p2.y - p1.y;

    p1.x = fmod(p1.x, 100);
    p1.y = fmod(p1.y, 100);
    p2.x = p1.x + width;
    p2.y = p1.y + height;
}

ShapePtrVctr Rectangle::disband() {

}
