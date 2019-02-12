#include "freedraw.h"

FreeDraw::FreeDraw()
{

}

void FreeDraw::draw(QPainter* painter) {
    painter->setPen(pen);
    painter->drawPath(path);
}

void FreeDraw::mousePressEvent(QMouseEvent *event) {
    path.moveTo(event->localPos().x(), event->localPos().y());
}

void FreeDraw::mouseMoveEvent(QMouseEvent *event) {
    if((std::abs((event->localPos().x() - path.currentPosition().x())) > 0.1)
            || (std::abs((event->localPos().y() - path.currentPosition().y())) > 0.1)) {
        path.lineTo(event->localPos().x(), event->localPos().y());
    }
}

void FreeDraw::mouseReleaseEvent(QMouseEvent *event) {
    path.closeSubpath();
}

void FreeDraw::mousePressEventSelect(QMouseEvent *event) {
    if(clickedIn(event)) {
        movePoint = {event->localPos().x(), event->localPos().y()};
        isMoving = true;
    }
}

void FreeDraw::mouseMoveEventSelect(QMouseEvent *event) {
    if(isMoving) {
        path.translate(event->localPos().x() - movePoint.x, event->localPos().y() - movePoint.y);
        movePoint = {event->localPos().x(), event->localPos().y()};
    }
}

void FreeDraw::mouseReleaseEventSelect(QMouseEvent *event) {
    isMoving = false;
}

//code to check for being clicked in, should they be members?

double FreeDraw::negDotProduct(Vec2d p1, Vec2d p2) {
    return p1.x * p2.x - p1.y * p2.y;
}

double FreeDraw::whichSide(Vec2d p1, Vec2d p2, Vec2d q1) {
    Vec2d a = {p2.y - p1.y, p2.x - p1.x};                                                       //is this the best way to do this?
    Vec2d b = {q1.x - p1.x, q1.y - p1.y};                                                       //this is for contained polygons, even connected polygons will have many lines to go through

    return negDotProduct(a, b);
}

bool FreeDraw::lineSegsIntersect(Vec2d p1, Vec2d p2, Vec2d q1, Vec2d q2) {
    return ((whichSide(p1, p2, q1) * (whichSide(p1, p2, q2)) < 0) && ((whichSide(q1, q2, p1)) * (whichSide(q1, q2, p2)) < 0));
}

bool FreeDraw::clickedIn(QMouseEvent *event) {
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
