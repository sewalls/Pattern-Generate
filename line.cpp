#include "line.h"

Line::Line() {

}

Line::Line(Vec2d p1, Vec2d p2)
{
    this->p1 = p1;
    this->p2 = p2;
}

void Line::draw(QPainter *painter) {
    if(currentState == Moving) {
        pen.setWidth(10);
    }
    painter->setPen(pen);
    painter->drawLine(QLineF{p1.x, p1.y, p2.x, p2.y});
}

void Line::mousePressEvent(QMouseEvent *event) {
    switch(currentState) {
    case Precreated: {
        p1 = {event->localPos().x(), event->localPos().y()};
        p2 = {event->localPos().x(), event->localPos().y()};   //this is so that it doesn't instantly draw a line from p1 to (0, 0)
        currentState = Creating;
        break;
    }
    case Creating: {
        currentState = Finished;
        break;
    }
    case Moving: {
        if(distanceClicked(event) < 10) {
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

void Line::mouseMoveEvent(QMouseEvent *event) {
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

void Line::mouseReleaseEvent(QMouseEvent *event) {
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

void Line::mousePressEventSelect(QMouseEvent *event) {
    if(distanceClicked(event) < 10) {
        isMoving = true;
        movePoint = {event->localPos().x(), event->localPos().y()};
    }
}

void Line::mouseMoveEventSelect(QMouseEvent *event) {
    if(isMoving) {
        p1.translate(event->localPos().x() - movePoint.x, event->localPos().y() - movePoint.y);
        p2.translate(event->localPos().x() - movePoint.x, event->localPos().y() - movePoint.y);
        movePoint = {event->localPos().x(), event->localPos().y()};
    }
}

void Line::mouseReleaseEventSelect(QMouseEvent *event) {
    isMoving = false;
}

double Line::distanceClicked(QMouseEvent *event) {
    Vec2d p = {event->localPos().x(), event->localPos().y()};
    Vec2d b;
    double t = ((p - p1) * (p2 - p1)) / ((p2 - p1).lengthSquared());

    (((p1 - p).lengthSquared() > (p2 - p).lengthSquared()) ? b = p1 - p : b = p2 - p);

    if(0 < t && t < 1) {
        b = (p1 + (p2 - p1).scaled(t)) - p; //finish
    }

    return sqrt(b.lengthSquared());
}
