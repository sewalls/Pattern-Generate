#include "rectangle.h"

Rectangle::Rectangle()
{

}

void Rectangle::draw(QPainter *painter) {
    brush.setStyle(Qt::SolidPattern);
    painter->setPen(pen);
    painter->setBrush(brush);
    painter->drawRect(QRectF{p1.x, p1.y, p2.x - p1.x, p2.y - p1.y});
}

void Rectangle::draw(QPainter *painter, Vec2d offset) {
    brush.setStyle(Qt::SolidPattern);
    painter->setPen(pen);
    painter->setBrush(brush);
    painter->drawRect(QRectF{p1.x + offset.x, p1.y + offset.y, p2.x - p1.x, p2.y - p1.y});
}

std::vector<Vec2d> Rectangle::boundingRect() {
    return {{std::min(p1.x, p2.x), std::min(p1.y, p2.y)}, {std::max(p1.x, p2.x), std::max(p1.y, p2.y)}};
}

void Rectangle::mousePressEvent(QMouseEvent *event) {
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

void Rectangle::mouseMoveEvent(QMouseEvent *event) {
    switch(currentState) {
    case State::Creating:
        p2 = {EX, EY};
        if(event->modifiers() == Qt::ShiftModifier) {
            p2 = {EX, p1.y + (EX - p1.x)};
        }
        break;
    case State::Moving:
        translate({EX - movePoint.x, EY - movePoint.y});
        movePoint = {EX, EY};
        break;
    default:
        break;
    }
}

bool Rectangle::isClickedOn(QMouseEvent *event) {

    if((EX > p2.x && EX < p1.x) || (EX > p1.x && EX < p2.x)) {
        if((EY > p2.y && EY < p1.y) || (EY > p1.y && EY < p2.y)) {
            return true;
        }
    }
    return false;
}

void Rectangle::translate(Vec2d translateBy) {
    p1.translate(translateBy.x, translateBy.y);
    p2.translate(translateBy.x, translateBy.y);
}

//void Rectangle::normalize(int scale) { //you made all the normalize functions have scale ints so that you didnt have to make a new shape scale function, fix this. see ifnormalize is needed at all anywhere
//    Vec2d n1 = {std::min(p1.x, p2.x), std::min(p1.y, p2.y)};
//    Vec2d n2 = {std::max(p1.x, p2.x), std::max(p1.y, p2.y)};
//    p1 = n1;
//    p2 = n2;

//    double width = p2.x - p1.x;
//    double height = p2.y - p1.y;

//    p1.x = fmod(p1.x, 100);
//    p1.y = fmod(p1.y, 100);
//    p2.x = p1.x + width;
//    p2.y = p1.y + height;
//}

ShapePtrVctr Rectangle::disband() {return ShapePtrVctr{};}
void Rectangle::tile() {}
