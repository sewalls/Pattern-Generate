#include "line.h"

Line::Line()
{

}

void Line::draw(QPainter *painter) {
    painter->setPen(pen);
    painter->drawLine(QLineF{p1.x, p1.y, p2.x, p2.y});
}

void Line::draw(QPainter *painter, Vec2d offset) {
    painter->setPen(pen);
    painter->drawLine(QLineF{p1.x + offset.x, p1.y + offset.y, p2.x + offset.x, p2.y + offset.y});
}

std::vector<Vec2d> Line::boundingRect() {
    return {{std::min(p1.x, p2.x), std::min(p1.y, p2.y)}, {std::max(p1.x, p2.x), std::max(p1.y, p2.y)}};
}

void Line::mousePressEvent(QMouseEvent *event) {
    switch(currentState) {
    case State::Precreated:
        p1 = {EX, EY};
        p2 = {EX, EY};
        currentState = State::Creating;
        break;
    case State::Creating:
        currentState = State::Finished;
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

void Line::mouseMoveEvent(QMouseEvent *event) {
    switch(currentState) {
    case State::Creating:
        p2 = {EX, EY};
        if(event->modifiers() == Qt::ShiftModifier) {
            if(EX > p1.x && EY > p1.y) {
                p2 = {EX, p1.y + (EX - p1.x)};
            }
            if(EX < p1.x && EY > p1.y) {
                p2 = {EX, p1.y - (EX - p1.x)};
            }
            if(EX > p1.x && EY < p1.y) {
                p2 = {EX, p1.y - (EX - p1.x)};
            }
            if(EX < p1.x && EY < p1.y) {
                p2 = {EX, p1.y + (EX - p1.x)};
            }
        }
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

bool Line::isClickedOn(QMouseEvent* event) {
    Vec2d p = {EX, EY};
    Vec2d b;
    double t = ((p - p1) * (p2 - p1)) / ((p2 - p1).lengthSquared());

    (((p1 - p).lengthSquared() > (p2 - p).lengthSquared()) ? b = p1 - p : b = p2 - p);

    if(0 < t && t < 1) {
        b = (p1 + (p2 - p1).scaled(t)) - p;
    }

    return sqrt(b.lengthSquared()) < 10;
}

void Line::translate(Vec2d translateBy) {
    p1.translate(translateBy.x, translateBy.y);
    p2.translate(translateBy.x, translateBy.y);
}

ShapePtrVctr Line::disband() {return ShapePtrVctr{};}
void Line::tile() {}
