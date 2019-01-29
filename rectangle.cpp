#include "rectangle.h"

Rectangle::Rectangle(Vec2d p1, Vec2d p2)
{
    this->p1 = p1;
    this->p2 = p2;
}

int Rectangle::width() {
    return p2.x() - p1.x();
}

int Rectangle::height() {
    return p2.y() - p1.y();
}

void Rectangle::draw(QPainter* painter) {

    painter->drawRect(p1.x(), p1.y(), width(), height()); // is this resource inefficient?
}
