#include "ellipse.h"

Ellipse::Ellipse(Vec2d p1, Vec2d p2) {
    this->p1 = p1;
    this->w = p2.x() - p1.x();
    this->h = p2.y() - p1.y();
}

Ellipse::Ellipse(Vec2d p1, int w, int h) {
    this->p1 = p1;
    this->w = w;
    this->h = h;
}

void Ellipse::draw(QPainter* painter) {
    painter->drawEllipse(p1.x(), p1.y(), w, h);
}
