#include "group.h"

Group::Group()
{

}

void Group::draw(QPainter *painter) {
    for(auto& obj:childShapes) {
        obj->draw(painter);
    }
}

void Group::mousePressEvent(QMouseEvent *event) {

}

void Group::mouseMoveEvent(QMouseEvent *event) {

}

void Group::mouseReleaseEvent(QMouseEvent */*event*/) { //currently marked unused to silence warnings

}

bool Group::isClickedOn(QMouseEvent* event) {

}

void Group::translate(Vec2d translateBy) {

}
