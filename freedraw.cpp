#include "freedraw.h"

FreeDraw::FreeDraw()
{

}

void FreeDraw::draw(QPainter* painter) {
    painter->setPen(pen);
    painter->drawPath(path);
}

void FreeDraw::drawSelected(QPainter* painter) {
    pen.setStyle(Qt::DashDotLine);
    painter->setPen(pen);
    painter->drawPath(path);
}

void FreeDraw::mousePressEvent(QMouseEvent *event) {
    switch(currentState) {
    case Precreated: {
        path.moveTo(event->localPos().x(), event->localPos().y());
        currentState = Creating;
        break;
    }
    case Creating: {
        path.moveTo(event->localPos().x(), event->localPos().y());
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

void FreeDraw::mouseMoveEvent(QMouseEvent *event) { //click to click vs click and hold, figure out how to separate these two
    switch(currentState) {
    case Precreated: {

        break;
    }
    case Creating: {
        if((std::abs((event->localPos().x() - path.currentPosition().x())) > 0.1)
                || (std::abs((event->localPos().y() - path.currentPosition().y())) > 0.1)) {
            path.lineTo(event->localPos().x(), event->localPos().y());
        }
        break;
    }
    case Moving: {
        path.translate(event->localPos().x() - movePoint.x, event->localPos().y() - movePoint.y);
        movePoint = {event->localPos().x(), event->localPos().y()};
        break;
    }
    case Finished: {

        break;
    }
    }
}

void FreeDraw::mouseReleaseEvent(QMouseEvent *event) {
    switch(currentState) {
    case Precreated: {

        break;
    }
    case Creating: {
        currentState = Finished;
        break;
    }
    case Moving: {
        currentState = Finished;
        break;
    }
    case Finished: {

        break;
    }
    }
}

bool FreeDraw::isClickedOn(QMouseEvent *event) {
    Vec2d p = {event->localPos().x(), event->localPos().y()};
    Vec2d b;
    Vec2d p1;
    Vec2d p2;

    double distance = 1000000; //arbitrarily large number for original comparison point

    for(int i = 0; i < path.elementCount() - 1; i++) {
        p1 = {path.elementAt(i).x, path.elementAt(i).y};
        p2 = {path.elementAt(i+1).x, path.elementAt(i+1).y};
        double t = ((p - p1) * (p2 - p1)) / ((p2 - p1).lengthSquared());

        (((p1 - p).lengthSquared() > (p2 - p).lengthSquared()) ? b = p1 - p : b = p2 - p);

        if(0 < t && t < 1) {
            b = (p1 + (p2 - p1).scaled(t)) - p;
        }

        if(sqrt(b.lengthSquared()) < distance) {
            distance = sqrt(b.lengthSquared());
        }
    }

    if(distance < 10) { //the integer here is the tolerance for "being close"
        return true;
    }
    return false;
}
