#include "group.h"

const double maxSize = 15;

Group::Group()
{

}

void Group::draw(QPainter *painter) {
    std::sort(childShapes.begin(), childShapes.end(), [](std::unique_ptr<Shape>& a, std::unique_ptr<Shape>& b) {
        return a->index < b->index;
    });
    brush.setStyle(Qt::SolidPattern);
    if(isTiling) {
        Vec2d tileRect = {0, 0};
        for(auto& obj:childShapes) {
            tileRect.x = std::max(tileRect.x, obj->boundingRect().x);
            tileRect.y = std::max(tileRect.y, obj->boundingRect().y);
        }
        if(tileRect.x < maxSize) {tileRect.x = maxSize;}
        if(tileRect.y < maxSize) {tileRect.y = maxSize;}

        for(auto& obj:childShapes) {
            for(double x = 0; x < 1600; x += tileRect.x) {
                for(double y = 0; y < 900; y += tileRect.y) {
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
    if(!isTiling) {
        for(auto& obj:childShapes) {
            obj->draw(painter, offset);
        }
    }
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
    std::vector<Vec2d> tileRect;
}

void Group::translate(Vec2d translateBy) {
    for(auto& obj:childShapes) {
        obj->translate(translateBy);
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

Vec2d Group::boundingRect() {
    Vec2d p2 = {0, 0};

    for(auto& obj:childShapes) {
        p2 = {std::max(p2.x, obj->boundingRect().x), std::max(p2.y, obj->boundingRect().y)};
    }

    return p2;
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


void Group::changePen(QPen pen) {
    for(auto& obj:childShapes) {
        obj->changePen(pen);
    }
}

void Group::changeBrush(QBrush brush) {
    for(auto& obj:childShapes) {
        obj->changeBrush(brush);
    }
}
