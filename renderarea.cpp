#include "renderarea.h"

RenderArea::RenderArea(QWidget *parent)
    : QWidget(parent), selectGroup{new Group}
{
    setFocusPolicy(Qt::StrongFocus);
    setFocus();

    grabKeyboard();

    pen.setColor(Qt::black);
    brush.setColor(Qt::transparent);

    pen.setStyle(Qt::DashLine);
    selectBox.changePen(pen);
    tileBox.changePen(pen);
    pen.setStyle(Qt::SolidLine);
    selectBox.changeBrush(brush);
    tileBox.changeBrush(brush);
}

void RenderArea::paintEvent(QPaintEvent *) {
    QPainter painter(this);

    painter.drawText(5, 10, QString::fromStdString(std::to_string(static_cast<int>(masterState))));
    painter.drawText(15, 10, QString::fromStdString(std::to_string(selectGroup->childShapes.size())));
    painter.drawText(35, 10, QString::fromStdString(std::to_string(hasFocus())));

    for(auto& obj:shapes) {
        obj->draw(&painter);
    }

    if(activeShape) {
        painter.drawText(25, 10, QString::fromStdString(std::to_string(activeShape->index)));
    }

    selectGroup->changePen(pen);
    selectGroup->changeBrush(brush);
    selectGroup->draw(&painter);
    selectBox.draw(&painter);
}

void RenderArea::mousePressEvent(QMouseEvent *event) {
    if(shapeToggled == ShapeName::Select) {
        activeShape = nullptr;
        masterState = State::Finished;

        if(event->modifiers() == Qt::ControlModifier) {
            setActiveShape(selectGroup.get());
            for(unsigned int i = 0; i < shapes.size(); i++) {
                if(shapes[i]->isClickedOn(event)) {
                    selectGroup->childShapes.push_back(std::move(shapes[i]));
                    shapes.erase(shapes.begin() + static_cast<int>(i));
                }
            }
        }

        if(event->modifiers() == Qt::ShiftModifier) {
            selectBox.currentState = State::Precreated;
            selectBox.mousePressEvent(event);
        }

        else {
            for(auto& obj:shapes) {
                if(obj->isClickedOn(event)) {
                    setActiveShape(obj.get());
                }
            }
            if(selectGroup->isClickedOn(event)) {
                setActiveShape(selectGroup.get());
            }
        }

        if(activeShape) {
            activeShape->currentState = State::Moving;
        }
    }

    else if(masterState == State::Finished) {
        switch(shapeToggled) {
        case ShapeName::Rectangle:
            addShape<Rectangle>();
            break;
        case ShapeName::Line:
            addShape<Line>();
            break;
        case ShapeName::Ellipse:
            addShape<Ellipse>();
            break;
        case ShapeName::Polygon:
            addShape<Polygon>();
            break;
        default:
            break;
        }
    }

    for(auto& obj:shapes) {
        obj->mousePressEvent(event);
    }
    selectGroup->mousePressEvent(event);
    updateMasterState();
}

void RenderArea::mouseMoveEvent(QMouseEvent *event) {
    if(shapeToggled == ShapeName::Select && event->modifiers() == Qt::ShiftModifier) {
        Vec2d eventOrig = {event->localPos().x(), event->localPos().y()};
        selectBox.mouseMoveEvent(event);
        Vec2d p1 = {std::min(selectBox.p1.x, selectBox.p2.x), std::min(selectBox.p1.y, selectBox.p2.y)};
        Vec2d p2 = {std::max(selectBox.p1.x, selectBox.p2.x), std::max(selectBox.p1.y, selectBox.p2.y)};
        std::vector<Vec2d> points;
        points.clear();

        for(double x = p1.x; x < p2.x; x += (p2.x - p1.x) / 20) {
            for(double y = p1.y; y < p2.y; y += (p2.y - p1.y) / 20 ) {
                points.push_back({x, y});
            }
        }

        for(unsigned int i = 0; i < shapes.size(); i++) {
            bool clicked = false;
            for(auto& point:points) {
                event->setLocalPos({point.x, point.y});
                if(shapes[i]->isClickedOn(event)) {
                    clicked = true;
                }
            }
            if(clicked) {
                selectGroup->childShapes.push_back(std::move(shapes[i]));
                shapes.erase(shapes.begin() + static_cast<int>(i));
            }
        }

        event->setLocalPos({eventOrig.x, eventOrig.y}); //make the new group the active shape?
    }

    for(auto& obj:shapes) {
        obj->mouseMoveEvent(event);
    }
    selectGroup->mouseMoveEvent(event);
    updateMasterState();
}

void RenderArea::mouseReleaseEvent(QMouseEvent *event) {
    selectBox.p1 = {0, 0};
    selectBox.p2 = {0, 0};
    if(selectGroup->childShapes.size() > 0) {
        std::unique_ptr<Group> group = std::make_unique<Group>();
        for(unsigned int i = 0; i < selectGroup->childShapes.size(); i++) {
            group->childShapes.push_back(std::move(selectGroup->childShapes[i]));
        }
        selectGroup->childShapes.clear();
        group->index = group->childShapes[0]->index;
        group->changePen(pen);
        group->changeBrush(brush);
        group->isTiling = selectGroup->isTiling;
        shapes.push_back(std::move(group));
    }
    for(auto& obj:shapes) {
        obj->mouseReleaseEvent(event);
    }
    selectGroup->mouseReleaseEvent(event);
    updateMasterState();
}

void RenderArea::keyPressEvent(QKeyEvent *event) {
    switch(event->key()) {
    case(Qt::Key_C):
        shapes.clear();
        selectGroup->childShapes.clear();
        masterIndex = 0;
        activeShape = nullptr;
        updateMasterState();
        break;
    case(Qt::Key_R):
        shapeToggled = ShapeName::Rectangle;
        break;
    case(Qt::Key_E):
        shapeToggled = ShapeName::Ellipse;
        break;
    case(Qt::Key_L):
        shapeToggled = ShapeName::Line;
        break;
    case(Qt::Key_P):
        shapeToggled = ShapeName::Polygon;
        break;
    case(Qt::Key_S):
        shapeToggled = ShapeName::Select;
        break;
//    case(Qt::Key_Right):
//        activeShape->translate({1, 0});
//        break;
//    case(Qt::Key_Left):
//        activeShape->translate({-1, 0});
//        break;
    default:
        break;
    }
}

void RenderArea::colorPenOpened() {
    QColorDialog dialog;  //move to function
    dialog.setOption(QColorDialog::ShowAlphaChannel);
    pen.setColor(dialog.getColor(Qt::black, this, "Pick a Color", dialog.options()));
    if(activeShape) {
        activeShape->changePen(pen);
    }
}

void RenderArea::colorBrushOpened() {
    QColorDialog dialog;
    dialog.setOption(QColorDialog::ShowAlphaChannel);
    brush.setColor(dialog.getColor(Qt::transparent, this, "Pick a Color", dialog.options()));
    if(activeShape) {
        activeShape->changeBrush(brush);
    }
}

void RenderArea::setActiveShape(Shape *shape) {
    if(activeShape != shape) {
        if(activeShape) {
            activeShape->currentState = State::Finished;
        }
        activeShape = shape;
    }
}

void RenderArea::updateMasterState() { //stuff that continually needs to be redone. probably is lazy programming
    if(activeShape) {
        masterState = activeShape->currentState;
    }

    std::sort(shapes.begin(), shapes.end(), [](std::unique_ptr<Shape>& a, std::unique_ptr<Shape>& b) {
        return a->index < b->index;
    });
    update();
}

void RenderArea::disbandGroup() {
    ShapePtrVctr returnShapes = activeShape->disband();
    //    for(auto& obj:returnShapes) {
    //        shapes.push_back(std::move(obj));
    //    }
    //    selectGroup->tile();
}

void RenderArea::tileStart() {
    selectGroup->tile();
}

template<typename T>
T* RenderArea::addShape() {
    auto shape = std::make_unique<T>();
    shape->changePen(pen);
    shape->changeBrush(brush);
    shape->index = masterIndex;
    masterIndex++;
    activeShape = shape.get();
    shapes.push_back(std::move(shape));
    return static_cast<T*>(activeShape);
}
