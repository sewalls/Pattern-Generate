#include "rectangle.h"

Rectangle::Rectangle() {

}

Rectangle::Rectangle(Vec2d p1, Vec2d p2)
{
    this->p1 = p1;
    this->p2 = p2;
}

Rectangle::Rectangle(Vec2d p1, double w, double h) {
    this->p1 = p1;
    p2 = {p1.x - w, p1.y - h};
}

void Rectangle::draw(QPainter* painter) {
    painter->setPen(pen);
    painter->drawRect(QRectF{p1.x, p1.y, width(), height()}); // is this resource inefficient?
}

void Rectangle::mousePressEvent(QMouseEvent *event) {
    switch(currentState) {
    case Precreated: {
        p1 = {event->localPos().x(), event->localPos().y()};
        p2 = {event->localPos().x(), event->localPos().y()};
        currentState = Creating;
        break;
    }
    case Creating: {
        currentState = Finished;
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

        break;
    }
    }
}

void Rectangle::mouseMoveEvent(QMouseEvent *event) {
    switch(currentState) {
    case Precreated: {

        break;
    }
    case Creating: {
        if(event->buttons() == Qt::LeftButton) {
            p2 = {event->localPos().x(), event->localPos().y()};
        }
        break;
    }
    case Moving: {
        if(event->buttons() == Qt::LeftButton)  {
            p1.translate(event->localPos().x() - movePoint.x, event->localPos().y() - movePoint.y);
            p2.translate(event->localPos().x() - movePoint.x, event->localPos().y() - movePoint.y);
            movePoint = {event->localPos().x(), event->localPos().y()};
        }
        break;
    }
    case Finished: {

        break;
    }
    }
}

void Rectangle::mouseReleaseEvent(QMouseEvent *event) {
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

bool Rectangle::isClickedOn(QMouseEvent *event) {
    if((event->localPos().x() > p2.x && event->localPos().x() < p1.x) || (event->localPos().x() > p1.x && event->localPos().x() < p2.x)) {
        if((event->localPos().y() > p2.y && event->localPos().y() < p1.y) || (event->localPos().y() > p1.y && event->localPos().y() < p2.y)) {
            return true;
        }
    }
    return false;
}

double Rectangle::width() {
    return p2.x - p1.x;
}

double Rectangle::height() {
    return p2.y - p1.y;
}
