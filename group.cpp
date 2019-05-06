#include "group.h"

Group::Group()
{

}

void Group::draw(QPainter *painter) {
    std::sort(childShapes.begin(), childShapes.end(), [](std::unique_ptr<Shape>& a, std::unique_ptr<Shape>& b) {
        return a->index < b->index;
    });
    brush.setStyle(Qt::SolidPattern);
    if(isTiling) {
        std::vector<Vec2d> tileRect = {{0, 0}, {0, 0}};
        for(auto& obj:childShapes) {
            tileRect[1].x = std::max(tileRect[1].x, obj->boundingRect()[1].x);
            tileRect[1].y = std::max(tileRect[1].y, obj->boundingRect()[1].y);
        }

        for(auto& obj:childShapes) {
            for(double x = 0; x < 1600; x += tileRect[1].x) {
                for(double y = 0; y < 900; y += tileRect[1].y) {
                    obj->draw(painter, {x, y});
                }
            }
        }
    }

    if(!isTiling) {
        for(auto& obj:childShapes) {
            obj->draw(painter);
        }
    }
}

void Group::draw(QPainter *painter, Vec2d offset) {
//    if(!isTiling) {
//        for(auto& obj:childShapes) {
//            obj->draw(painter, offset);
//        }
//    }
}

std::vector<Vec2d> Group::boundingRect() {
    Vec2d p1 = {0, 0};
    Vec2d p2 = {0, 0};

    for(auto& obj:childShapes) {
        p2 = {std::max(p2.x, obj->boundingRect()[1].x), std::max(p2.y, obj->boundingRect()[1].y)};
    }

    return {p1, p2};
}

void Group::mousePressEvent(QMouseEvent *event) {
    switch(currentState) {
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

void Group::mouseMoveEvent(QMouseEvent *event) {
    if(currentState == State::Moving) {
        translate({EX - movePoint.x, EY - movePoint.y});
        movePoint = {EX, EY};
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

void Group::translate(Vec2d translateBy) {
    for(auto& obj:childShapes) {
        obj->translate(translateBy);
    }
}

ShapePtrVctr Group::disband() {
    ShapePtrVctr returnShapes;
    for(auto& obj:childShapes) {
        returnShapes.push_back(std::move(obj));
    }
    childShapes.clear();
    return returnShapes;
}

void Group::tile() {
    isTiling = !isTiling;
}
