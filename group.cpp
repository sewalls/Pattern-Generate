#include "group.h"

Group::Group()
{

}

void Group::draw(QPainter *painter) {
    for(auto& obj:childShapes) {
        obj->draw(painter);
    }
}

void Group::drawTiled(QPainter *painter) {
    for(auto& obj:childShapes) { //just messing around with
        for(double i = 0; i < 2000; i += 100) {
            for(double j = 0; j < 2000; j += 100) {
                obj->draw(painter);
                obj->translate({i, j});
                obj->draw(painter);
                obj->translate({-i, -j});
            }
        }
    }
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
