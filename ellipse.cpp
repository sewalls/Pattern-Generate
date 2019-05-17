#include "ellipse.h"

const double pi = 3.14159;

Ellipse::Ellipse()
{

}

void Ellipse::draw(QPainter *painter) {
    std::vector<Vec2d> points = param();
    brush.setStyle(Qt::SolidPattern);
    painter->setPen(pen);
    painter->setBrush(brush);
    painter->drawEllipse(QRectF{p1.x, p1.y, p2.x - p1.x, p2.y - p1.y});
}

void Ellipse::draw(QPainter *painter, Vec2d offset) {
    std::vector<Vec2d> points = param();
    brush.setStyle(Qt::SolidPattern);
    painter->setPen(pen);
    painter->setBrush(brush);
    painter->drawEllipse(QRectF{p1.x + offset.x, p1.y + offset.y, p2.x - p1.x, p2.y - p1.y});
}

void Ellipse::mousePressEvent(QMouseEvent *event) {
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

void Ellipse::mouseMoveEvent(QMouseEvent *event) {
    switch(currentState) {
    case State::Creating:
        p2 = {EX, EY};
        if(event->modifiers() == Qt::ShiftModifier) {
            p2 = {EX, p1.y + (EX - p1.x)};
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

void Ellipse::translate(Vec2d translateBy) {
    p1.translate(translateBy.x, translateBy.y);
    p2.translate(translateBy.x, translateBy.y);
}

bool Ellipse::isClickedOn(QMouseEvent *event) {
    std::vector<Vec2d> points = param();
    Vec2d u = {EX, EY};
    Vec2d v = {EX + 10000, EY};

    int count = 0;

    if(lineSegsIntersect(u, v, points[points.size() - 1], points[0])) {
        count++;
    }

    for(unsigned int i = 0; i < points.size() - 1; i++) {
        if(lineSegsIntersect(u, v, points[i], points[i+1])) {
            count++;
        }
    }

    return count % 2;
}

Vec2d Ellipse::boundingRect() {
    return {std::max(p1.x, p2.x), std::max(p1.y, p2.y)};
}

std::vector<Vec2d> Ellipse::param() {
    std::vector<Vec2d> points;
    double a = (p2.x - p1.x) / 2;
    double b = (p2.y - p1.y) / 2;

    for(double t = 0; t < 2*pi; t += pi / 32) {
        points.push_back({a*cos(t), b*sin(t)});
    }
    for(unsigned int i = 0; i < points.size(); i++) {
        points[i].translate(p1.x + a, p1.y + b);
    }
    return points;
}
