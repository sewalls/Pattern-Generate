#include "polyline.h"

PolyLine::PolyLine()
{

}

void PolyLine::draw(QPainter* painter) {
    painter->setPen(pen);
    painter->drawPath(path);
}

void PolyLine::mousePressEvent(QMouseEvent *event) {
    switch(currentState) {
    case Precreated: {
        path.moveTo(event->localPos().x(), event->localPos().y());
        currentState = Creating;
        break;
    }
    case Creating: {
        if(abs(event->localPos().x() - path.elementAt(0).x) < 5 ||
                abs(event->localPos().y() - path.elementAt(0).y) < 5) {
            path.closeSubpath();
            currentState = Finished;
        }
        else {
            path.lineTo(event->localPos().x(), event->localPos().y());
        }
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

void PolyLine::mouseMoveEvent(QMouseEvent *event) {
    switch(currentState) {
    case Precreated: {

        break;
    }
    case Creating: {

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

void PolyLine::mouseReleaseEvent(QMouseEvent *event) {
    switch(currentState) {
    case Precreated: {

        break;
    }
    case Creating: {

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

bool PolyLine::isClickedOn(QMouseEvent *event) {
    Vec2d u = {event->localPos().x(), event->localPos().y()};
    Vec2d v = {event->localPos().x() + 10000, event->localPos().y()};

    int count = 0;

    if(lineSegsIntersect(u, v, {path.currentPosition().x(), path.currentPosition().y()}, {path.elementAt(0).x, path.elementAt(0).y})) {
        count++;
    }

    for(int i = 0; i < path.elementCount() - 1; i++) {
        if(lineSegsIntersect(u, v, {path.elementAt(i).x, path.elementAt(i).y}, {path.elementAt(i+1).x, path.elementAt(i+1).y})) {
            count++;
        }
    }

    return count % 2;
}

double PolyLine::negDotProduct(Vec2d p1, Vec2d p2) {
    return p1.x * p2.x - p1.y * p2.y;
}

double PolyLine::whichSide(Vec2d p1, Vec2d p2, Vec2d q1) {
    Vec2d a = {p2.y - p1.y, p2.x - p1.x};                                                       //is this the best way to do this?
    Vec2d b = {q1.x - p1.x, q1.y - p1.y};                                                       //this is for contained polygons, even connected polygons will have many lines to go through

    return negDotProduct(a, b);
}

bool PolyLine::lineSegsIntersect(Vec2d p1, Vec2d p2, Vec2d q1, Vec2d q2) {
    return ((whichSide(p1, p2, q1) * (whichSide(p1, p2, q2)) < 0) && ((whichSide(q1, q2, p1)) * (whichSide(q1, q2, p2)) < 0));
}
