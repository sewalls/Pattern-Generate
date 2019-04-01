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
    pen.setStyle(Qt::SolidLine);
    selectBox.changeBrush(brush);
}

void RenderArea::paintEvent(QPaintEvent *) {
    QPainter painter(this);

    painter.drawText(5, 10, QString::fromStdString(std::to_string(static_cast<int>(masterState))));

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
    update();
}

void RenderArea::mouseMoveEvent(QMouseEvent *event) {
    if(shapeToggled == ShapeName::Select && event->modifiers() == Qt::ShiftModifier) {
        Vec2d eventOrig = {event->localPos().x(), event->localPos().y()};
        Vec2d p1 = {selectBox.p1.x, selectBox.p1.y};
        Vec2d p2 = {selectBox.p2.x, selectBox.p2.y};
        selectBox.mouseMoveEvent(event);
        std::vector<Vec2d> points;

        if(p1.x > p2.x) {
            double width = p1.x - p2.x;
            p1.x -= width;
            p2.x += width;
        }
        if(p1.y < p2.y) {
            double height = p2.y - p1.y;
            p1.y += height;
            p2.y -= height;
        }

        for(double x = p1.x; x < p2.x; x += (p2.x - p1.x) / 20) {
            for(double y = p1.y; y < p2.y; y += (p2.y - p1.y) / 20 ) {
                points.push_back({x, y});
            }
        }

        bool clicked;

        for(unsigned int i = 0; i < shapes.size(); i++) {
            clicked = false;
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

        event->setLocalPos({eventOrig.x, eventOrig.y});
    }
    for(auto& obj:shapes) {
        obj->mouseMoveEvent(event);
    }
    selectGroup->mouseMoveEvent(event);

    updateMasterState();
    update();
}

void RenderArea::mouseReleaseEvent(QMouseEvent *event) {
    selectBox.p1 = {0, 0};
    selectBox.p2 = {0, 0};
    for(auto& obj:shapes) {
        obj->mouseReleaseEvent(event);
    }
    selectGroup->mouseReleaseEvent(event);

    updateMasterState();
    update();
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

void RenderArea::updateMasterState() {
    if(activeShape) {
        masterState = activeShape->currentState;
    }
}

void RenderArea::disbandGroup() {
    for(auto& obj:selectGroup->childShapes) {
        shapes.push_back(std::move(obj));
    }
    selectGroup->childShapes.clear();
    std::sort(shapes.begin(), shapes.end(), [](std::unique_ptr<Shape>& a, std::unique_ptr<Shape>& b) {
        return a->index < b->index;
    });
    shapes[0]->theta = (3.14159 / 4); //to test
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
