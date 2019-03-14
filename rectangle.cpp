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
    pen.setStyle(Qt::SolidLine);
    brush.setStyle(Qt::SolidPattern);
    painter->setBrush(brush);
    painter->setPen(pen);
    painter->drawRect(QRectF{p1.x, p1.y, width(), height()});
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

void Rectangle::mouseReleaseEvent(__attribute__((unused))QMouseEvent *event) { //currently marked unused to silence warnings
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

void Rectangle::translate(Vec2d translateBy) {
    p1.translate(translateBy.x, translateBy.y);
    p2.translate(translateBy.x, translateBy.y);
}

double Rectangle::width() {
    return p2.x - p1.x;
}

double Rectangle::height() {
    return p2.y - p1.y;
}
