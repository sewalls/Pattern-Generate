#include "group.h"

Group::Group()
{

}

void Group::draw(QPainter *painter) {
    brush.setStyle(Qt::SolidPattern);
    for(auto& obj:childShapes) {
        obj->fixOffscreen();
        obj->changePen(pen);
        obj->changeBrush(brush);
        obj->draw(painter);
    }
    //drawTiled(painter);
}

void Group::mousePressEvent(QMouseEvent *event) {
    switch(currentState) {
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

void Group::mouseMoveEvent(QMouseEvent *event) {
    if(currentState == State::Moving) {
        translate({event->localPos().x() - movePoint.x, event->localPos().y() - movePoint.y});
        movePoint = {event->localPos().x(), event->localPos().y()};
    }
}

bool Group::isClickedOn(QMouseEvent* event) {
    bool isClicked = false;

    for(auto& obj:childShapes) {
        if(obj->isClickedOn(event)) {
            isClicked = true;
        }
    }

    return isClicked;
}

void Group::fixOffscreen() {
    //todo
}

void Group::translate(Vec2d translateBy) {
    for(auto& obj:childShapes) {
        obj->translate(translateBy);
    }
}

ShapePtrVctr Group::disband() {
    ShapePtrVctr returnShapes;
    tile();
//    for(auto& obj:childShapes) {
//        returnShapes.push_back(std::move(obj));
//    }
//    childShapes.clear();
    return returnShapes;
}

Group* Group::clone_impl() const {
    for(auto& obj:childShapes) {

    }
}

void Group::tile() {
    Group newGroup;
    for(int x = 0; x < 16; x++) {
        for(int y = 0; y < 9; y++) {
            for(auto& obj:childShapes) {
                std::unique_ptr<Shape> newShape = obj->clone();
                newShape->translate({static_cast<double>(x * 100), static_cast<double>(y * 100)}); //dumb cast to get it to shut up
                newGroup.childShapes.push_back(std::move(newShape));
            }
        }
    }
    for(auto& obj:newGroup.childShapes) {
        childShapes.push_back(std::move(obj));
    }
}
