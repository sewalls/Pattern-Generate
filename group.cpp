#include "group.h"

Group::Group()
{

}

void Group::draw(QPainter *painter) {
    brush.setStyle(Qt::SolidPattern);
    for(auto& obj:childShapes) {
        obj->changePen(pen);
        obj->changeBrush(brush);
        obj->draw(painter);
    }
}

void Group::drawTiled(QPainter *painter) {

}

void Group::mousePressEvent(QMouseEvent *event) {
    switch(currentState) {
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

void Group::mouseMoveEvent(QMouseEvent *event) {
    if(currentState == State::Moving) {
        translate({event->localPos().x() - movePoint.x, event->localPos().y() - movePoint.y});
        movePoint = {event->localPos().x(), event->localPos().y()};
    }
}

bool Group::isClickedOn(QMouseEvent* event) {
    bool isClicked = false;

    for(auto& obj:childShapes) {
        if(obj->isClickedOn(event)) {
            isClicked = true;
        }
    }

    return isClicked;
}

void Group::translate(Vec2d translateBy) {
    for(auto& obj:childShapes) {
        obj->translate(translateBy);
    }
}
