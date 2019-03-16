#include "line.h"

Line::Line() {

}

Line::Line(Vec2d p1, Vec2d p2)
{
    this->p1 = p1;
    this->p2 = p2;
}

void Line::draw(QPainter *painter) {
    pen.setStyle(Qt::SolidLine);
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

void Line::mouseReleaseEvent(QMouseEvent */*event*/) { //currently marked unused to silence warnings
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

bool Line::isClickedOn(QMouseEvent* event) {
    return distanceClicked(event) < 10;
}

double Line::distanceClicked(QMouseEvent *event) {
    Vec2d p = {event->localPos().x(), event->localPos().y()};
    Vec2d b;
    double t = ((p - p1) * (p2 - p1)) / ((p2 - p1).lengthSquared());

    (((p1 - p).lengthSquared() > (p2 - p).lengthSquared()) ? b = p1 - p : b = p2 - p);

    if(0 < t && t < 1) {
        b = (p1 + (p2 - p1).scaled(t)) - p;
    }

    return sqrt(b.lengthSquared());
}

void Line::translate(Vec2d translateBy) {
    p1.translate(translateBy.x, translateBy.y);
    p2.translate(translateBy.x, translateBy.y);
}
