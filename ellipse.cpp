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

void Ellipse::mousePressEvent(QMouseEvent *event) {
    switch(currentState) {
    case State::Precreated:
        p1 = {event->localPos().x(), event->localPos().y()};
        p2 = {event->localPos().x(), event->localPos().y()};
        currentState = State::Creating;
        break;
    case State::Creating:
        currentState = State::Finished;
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

void Ellipse::mouseMoveEvent(QMouseEvent *event) {
    switch(currentState) {
    case State::Creating:
        p2 = {event->localPos().x(), event->localPos().y()};
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

bool Ellipse::isClickedOn(QMouseEvent *event) {
    std::vector<Vec2d> points = param();
    Vec2d u = {event->localPos().x(), event->localPos().y()};
    Vec2d v = {event->localPos().x() + 10000, event->localPos().y()};

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

void Ellipse::translate(Vec2d translateBy) {
    p1.translate(translateBy.x, translateBy.y);
    p2.translate(translateBy.x, translateBy.y);
}

void Ellipse::rotate(double theta) {

}

