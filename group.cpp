#include "group.h"

Group::Group()
{

}

void Group::draw(QPainter *painter) {
    for(auto& obj:childShapes) {
        obj->draw(painter);
    }
}

void Group::mousePressEvent(QMouseEvent *event) {
    switch(currentState) {
    case Precreated: {

        break;
    }
    case Creating: {

        break;
    }
    case Moving: {
        if(isClickedOn(event)) {
            movePoint = {event->localPos().x(), event->localPos().y()};
        }
        else {
            currentState = Finished;
        }
        break;
    }
    case Finished: {
        if(isClickedOn(event)) {
            currentState = Moving;
        }
        break;
    }
  }
}

void Group::mouseMoveEvent(QMouseEvent *event) {
    switch(currentState) {
    case Precreated: {

        break;
    }
    case Creating: {

        break;
    }
    case Moving: {
        if(event->buttons() == Qt::LeftButton)  {
            translate({event->localPos().x() - movePoint.x, event->localPos().y() - movePoint.y});
            movePoint = {event->localPos().x(), event->localPos().y()};
        }
        break;
    }
    case Finished: {

        break;
    }
  }
}

void Group::mouseReleaseEvent(QMouseEvent */*event*/) { //currently marked unused to silence warnings
    switch(currentState) {
    case Precreated: {

        break;
    }
    case Creating: {
        currentState = Finished;
        break;
    }
    case Moving: {

        break;
    }
    case Finished: {

        break;
    }
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
