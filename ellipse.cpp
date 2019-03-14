#include "ellipse.h"

const double pi = 3.14159;

Ellipse::Ellipse() {

}

Ellipse::Ellipse(Vec2d p1, Vec2d p2) {
    this->p1 = p1;
    this->p2 = p2;
}

Ellipse::Ellipse(Vec2d p1, double w, double h) {
    this->p1 = p1;
    p2 = {p1.x + w, p1.y + h};
}

void Ellipse::draw(QPainter* painter) {
    std::vector<Vec2d> points = param();
    brush.setStyle(Qt::SolidPattern);
    painter->setBrush(brush);
    painter->setPen(pen);
    //    Vec2d newP1 = {p1.x - 800, p1.y - 400};
    //    Vec2d newP2 = {p2.x - 800, p2.y - 400};
    ////    Vec2d newP1 = {fmod(p1.x, 800), fmod(p1.y, 400)};
    ////    Vec2d newP2 = {p2.x - p1.x, p2.y - p1.y};
    //    for(unsigned int i = 1; i <= 8; i++) { //these can be determined by screen height and width
    //        for(unsigned int j = 1; j <= 5; j++) {
    //            painter->drawEllipse(QRectF{newP1.x, newP1.y, newP2.x - newP1.x, newP2.y - newP1.y});
    //            newP1.translate(0, 200);
    //            newP2.translate(0, 200);
    //        }
    //        newP1.translate(200, -1000);
    //        newP2.translate(200, -1000);
    //    }
    painter->drawEllipse(QRectF{p1.x, p1.y, p2.x - p1.x, p2.y - p1.y});
    //    for(int i = 0; i < points.size() - 1; i++) { //for testing
    //        painter->drawLine(points[i].x, points[i].y, points[i+1].x, points[i+1].y);
    //    }
    //    painter->drawLine(points[points.size() - 1].x, points[points.size() - 1].y, points[0].x, points[0].y);
}

void Ellipse::mousePressEvent(QMouseEvent* event) {
    switch(currentState) {
    case Precreated: {
        p1 = {event->localPos().x(), event->localPos().y()};
        p2 = {event->localPos().x(), event->localPos().y()};
        currentState = Creating;
        break;
    }
    case Creating: {
        currentState = Finished;
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

void Ellipse::mouseMoveEvent(QMouseEvent *event) {
    switch(currentState) {
    case Precreated: {

        break;
    }
    case Creating: {
        if(event->buttons() == Qt::LeftButton) {
            p2 = {event->localPos().x(), event->localPos().y()};
        }
        break;
    }
    case Moving: {
        if(event->buttons() == Qt::LeftButton)  {
            translate({event->localPos().x() - movePoint.x, event->localPos().y() - movePoint.y});
            movePoint = {event->localPos().x(), event->localPos().y()};
        }
        break;
    }
    case Finished: {

        break;
    }
    }
}

void Ellipse::mouseReleaseEvent(__attribute__((unused))QMouseEvent *event) { //currently marked unused to silence warnings
    switch(currentState) {
    case Precreated: {

        break;
    }
    case Creating: {
        currentState = Finished;
        param();
        break;
    }
    case Moving: {

        break;
    }
    case Finished: {

        break;
    }
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

void Ellipse::translate(Vec2d translateBy) {
    p1.translate(translateBy.x, translateBy.y);
    p2.translate(translateBy.x, translateBy.y);
}

double negDotProduct(Vec2d p1, Vec2d p2) {
    return p1.x * p2.x - p1.y * p2.y;
}

double whichSide(Vec2d p1, Vec2d p2, Vec2d q1) {    //move to a new cpp?
    Vec2d a = {p2.y - p1.y, p2.x - p1.x};                                                       //is this the best way to do this?
    Vec2d b = {q1.x - p1.x, q1.y - p1.y};                                                       //this is for contained polygons, even connected polygons will have many lines to go through

    return negDotProduct(a, b);
}

bool lineSegsIntersect(Vec2d p1, Vec2d p2, Vec2d q1, Vec2d q2) {
    return ((whichSide(p1, p2, q1) * (whichSide(p1, p2, q2)) < 0) && ((whichSide(q1, q2, p1)) * (whichSide(q1, q2, p2)) < 0));
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

