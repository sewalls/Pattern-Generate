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

void Polygon::draw(QPainter *painter, Vec2d offset) {
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
        path.moveTo(EX, EY);
        currentState = State::Creating;
        break;
    case State::Creating:
        if(std::pow(EX - path.elementAt(0).x, 2) + std::pow(EY - path.elementAt(0).y, 2) < 20) {
            path.closeSubpath();
            currentState = State::Finished;
        }
        else {
            path.lineTo(EX, EY);
        }
        break;
    case State::Moving:
        if(isClickedOn(event)) {
            movePoint = {EX, EY};
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
        translate({EX - movePoint.x, EY - movePoint.y});
        movePoint = {EX, EY};
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
    Vec2d u = {EX, EY};
    Vec2d v = {EX + 10000, EY};

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

void Polygon::translate(Vec2d translateBy) {
    path.translate(translateBy.x, translateBy.y);
}

ShapePtrVctr Polygon::disband() {
    path.closeSubpath();
    currentState = State::Finished;
    return ShapePtrVctr{};
}

void Polygon::tile() {}
