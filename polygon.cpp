#include "Polygon.h"

Polygon::Polygon()
{

}

void Polygon::draw(QPainter *painter) {
    brush.setStyle(Qt::SolidPattern);
    painter->setPen(pen);
    painter->setBrush(brush);
    painter->drawPath(path);
    painter->fillPath(path, brush);
}

void Polygon::drawOffset(QPainter *painter, Vec2d offset) {
    QPainterPath newPath = path;
    newPath.translate(offset.x, offset.y);
    brush.setStyle(Qt::SolidPattern);
    painter->setPen(pen);
    painter->setBrush(brush);
    painter->drawPath(newPath);
    painter->fillPath(newPath, brush);
}

std::vector<Vec2d> Polygon::boundingRect() {
    Vec2d p1 = {0, 0};
    Vec2d p2 = {0, 0};

    for(int i = 0; i < path.elementCount(); i++) {
        //p1 = {std::max(p1.x, path.elementAt(i).x), std::max(p1.y, path.elementAt(i).y)};
        p2 = {std::max(p2.x, path.elementAt(i).x), std::max(p2.y, path.elementAt(i).y)};
    }

    return {p1, p2};
}

void Polygon::mousePressEvent(QMouseEvent *event) {
    switch(currentState) {
    case State::Precreated:
        path.moveTo(event->localPos().x(), event->localPos().y());
        currentState = State::Creating;
        break;
    case State::Creating:
        if(std::abs(event->localPos().x() - path.elementAt(0).x) < 5 ||
                std::abs(event->localPos().y() - path.elementAt(0).y) < 5) {
            path.closeSubpath();
            currentState = State::Finished;
        }
        else {
            path.lineTo(event->localPos().x(), event->localPos().y());
        }
        break;
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

void Polygon::mouseMoveEvent(QMouseEvent *event) {
    switch(currentState) {
    case State::Creating:
        break;
    case State::Moving: {
        translate({event->localPos().x() - movePoint.x, event->localPos().y() - movePoint.y});
        movePoint = {event->localPos().x(), event->localPos().y()};
        break;
    }
    default:
        break;
    }
}

void Polygon::mouseReleaseEvent(QMouseEvent *) {
    if(currentState == State::Moving) {
        currentState = State::Finished;
    }
}

bool Polygon::isClickedOn(QMouseEvent *event) {
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

void Polygon::fixOffscreen() {
    double smallestX = path.elementAt(0).x;
    double largestX  = path.elementAt(0).x;
    double smallestY = path.elementAt(0).y;
    double largestY  = path.elementAt(0).y;
    for(int i = 1; i < path.elementCount(); i++) {
        smallestX = std::min(smallestX, path.elementAt(i).x);
        largestX  = std::max(largestX, path.elementAt(i).x);
        smallestY = std::min(smallestY, path.elementAt(i).y);
        largestY  = std::max(largestY, path.elementAt(i).y);
    }

    if(smallestX > 1600) {
        translate({-1600, 0});
    }
    if(smallestY > 900) {
        translate({0, -900});
    }
    if(largestX < 0) {
        translate({1600, 0});
    }
    if(largestY < 0) {
        translate({0, 900});
    }
}

void Polygon::normalize(int scale) {

}

void Polygon::translate(Vec2d translateBy) {
    path.translate(translateBy.x, translateBy.y);
}

ShapePtrVctr Polygon::disband() {

}
