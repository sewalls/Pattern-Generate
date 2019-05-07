#include "renderarea.h"

RenderArea::RenderArea(QWidget *parent)
    : QWidget(parent), selectGroup{new Group}
{
    setFocusPolicy(Qt::StrongFocus);
    setFocus();

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
    painter.setRenderHint(QPainter::Antialiasing);

    painter.drawText(5, 10, QString::fromStdString(std::to_string(static_cast<int>(masterState))));
    painter.drawText(15, 10, QString::fromStdString(std::to_string(selectGroup->childShapes.size())));
    painter.drawText(35, 10, QString::fromStdString(std::to_string(hasFocus())));
    if(activeShape) {
        painter.drawText(25, 10, QString::fromStdString(std::to_string(activeShape->index)));
    }

    for(auto& obj:shapes) {
        obj->draw(&painter);
    }

    selectGroup->draw(&painter);
    selectBox.draw(&painter);
}

void RenderArea::mousePressEvent(QMouseEvent *event) {
    if(shapeToggled == ShapeName::Select) {
        activeShape = nullptr;
        masterState = State::Finished;

        if(event->modifiers() == Qt::ControlModifier) {
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
    if(shapeToggled == ShapeName::Select && event->modifiers() == Qt::ControlModifier) {
        Vec2d eventOrig = {EX, EY};
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
        activeShape = group.get();
        for(unsigned int i = 0; i < selectGroup->childShapes.size(); i++) {
            group->childShapes.push_back(std::move(selectGroup->childShapes[i]));
        }
        selectGroup->childShapes.clear();
        group->index = masterIndex;
        masterIndex++;
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
    case(Qt::Key_Backspace):
        shapes.erase(shapes.begin() + static_cast<int>(activeShapePosition()));
        masterState = State::Finished;
        activeShape = nullptr;
        update();
        break;
    case(Qt::Key_R):
        rectangleTrigger();
        break;
    case(Qt::Key_E):
        ellipseTrigger();
        break;
    case(Qt::Key_L):
        lineTrigger();
        break;
    case(Qt::Key_P):
        polygonTrigger();
        break;
    case(Qt::Key_S):
        selectTrigger();
        break;
    case(Qt::Key_Right):
        if(activeShape) {
            activeShape->translate({1, 0});
            update();
        }
        break;
    case(Qt::Key_Left):
        if(activeShape) {
            activeShape->translate({-1, 0});
            update();
        }
        break;
    case(Qt::Key_Up):
        if(activeShape) {
            activeShape->translate({0, -1});
            update();
        }
        break;
    case(Qt::Key_Down):
        if(activeShape) {
            activeShape->translate({0, 1});
            update();
        }
        break;
    default:
        break;
    }
}

void RenderArea::colorPenOpened() {
    QColorDialog dialog;  //move to function
    dialog.setOption(QColorDialog::ShowAlphaChannel);
    pen.setColor(dialog.getColor(Qt::black, this, "Pick a Color", dialog.options()));
    if(activeShape && shapeToggled == ShapeName::Select) {
        activeShape->changePen(pen);
    }
}

void RenderArea::colorBrushOpened() {
    QColorDialog dialog;
    dialog.setOption(QColorDialog::ShowAlphaChannel);
    brush.setColor(dialog.getColor(Qt::white, this, "Pick a Color", dialog.options()));
    if(activeShape && shapeToggled == ShapeName::Select) {
        activeShape->changeBrush(brush);
    }
}

void RenderArea::scalePrompt() {
    QInputDialog dialog;
    if(activeShape) {
        //activeShape->normalize(dialog.getInt(this, "Input Rotation", "title", 0, 0, 360, 1));
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
    for(auto& obj:returnShapes) {
        shapes.push_back(std::move(obj));
    }
}

void RenderArea::tileStart() {
    if(activeShape) {
        activeShape->tile();
    }
}

unsigned int RenderArea::activeShapePosition() {
    unsigned int pos = 0;
    for(unsigned int i = 0; i < shapes.size(); i++) {
        if(shapes[i].get() == activeShape) {
            pos = i;
        }
    }
    return pos;
}

void RenderArea::bringToFront() {
    if(activeShape) {
        for(unsigned int pos = activeShapePosition(); pos < shapes.size(); pos++) {
            bringForward();
        }
    }
}

void RenderArea::bringForward() { //this over-complicated code is because index != position in shapes vector, since groups "steal" other shapes
    if(activeShape) {
        std::sort(shapes.begin(), shapes.end(), [](std::unique_ptr<Shape>& a, std::unique_ptr<Shape>& b) {
            return a->index < b->index;
        });
        unsigned int pos = activeShapePosition();
        if(pos != shapes.size() - 1) {
            shapes[pos]->index = shapes[pos + 1]->index;
            shapes[pos + 1]->index = pos;
            std::sort(shapes.begin(), shapes.end(), [](std::unique_ptr<Shape>& a, std::unique_ptr<Shape>& b) {
                return a->index < b->index;
            });
        }
    }
}

void RenderArea::bringBackward() {
    if(activeShape) {
        std::sort(shapes.begin(), shapes.end(), [](std::unique_ptr<Shape>& a, std::unique_ptr<Shape>& b) {
            return a->index < b->index;
        });
        unsigned int pos = activeShapePosition();
        if(pos != 0) {
            shapes[pos]->index = shapes[pos - 1]->index;
            shapes[pos - 1]->index = pos;
            std::sort(shapes.begin(), shapes.end(), [](std::unique_ptr<Shape>& a, std::unique_ptr<Shape>& b) {
                return a->index < b->index;
            });
        }
    }
}

void RenderArea::bringToBack() {
    if(activeShape) {
        for(unsigned int pos = activeShapePosition(); pos > 0; pos--) {
            bringBackward();
        }
    }
}

void RenderArea::screenTest() {
    QPixmap pixmap(1547, 874); //weird-ass margins, don't ask
    QString string = QString::fromStdString(std::to_string(time(nullptr)));
    string.append(".png");
    this->render(&pixmap);
    pixmap.save(string);
}

void RenderArea::shapeToggleTrigger(ShapeName newShape) {
    if(shapeToggled == ShapeName::Polygon) {
        if(activeShape) {
            activeShape->disband();
        }
        masterState = State::Finished;
    }
    shapeToggled = newShape;
}

void RenderArea::ellipseTrigger() {
    shapeToggleTrigger(ShapeName::Ellipse);
}
void RenderArea::rectangleTrigger() {
    shapeToggleTrigger(ShapeName::Rectangle);
}
void RenderArea::lineTrigger() {
    shapeToggleTrigger(ShapeName::Line);
}
void RenderArea::polygonTrigger() {
    shapeToggled = ShapeName::Polygon;
}
void RenderArea::selectTrigger() {
    shapeToggleTrigger(ShapeName::Select);
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
