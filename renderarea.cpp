#include "renderarea.h"

RenderArea::RenderArea(QWidget *parent)
    : QWidget(parent), selectGroup{new Group}
{
    setFocusPolicy(Qt::StrongFocus);
    setFocus();

    pen.setColor(Qt::black);
    brush.setColor(Qt::transparent);


}

void RenderArea::paintEvent(QPaintEvent *) {
    QPainter painter(this);

    painter.drawText(5, 10, QString::fromStdString(std::to_string(static_cast<int>(masterState))));

    for(auto& obj:shapes) {
        obj->draw(&painter);
    }
    selectGroup->draw(&painter);
}

void RenderArea::mousePressEvent(QMouseEvent *event) {
    if(shapeToggled == ShapeName::Select) {
        activeShape = nullptr;
        masterState = State::Finished;

        if(event->modifiers() == Qt::ShiftModifier) {
            setActiveShape(selectGroup.get());
            for(unsigned int i = 0; i < shapes.size(); i++) {
                if(shapes[i]->isClickedOn(event)) {
                    selectGroup->childShapes.push_back(std::move(shapes[i]));
                    shapes.erase(shapes.begin() + static_cast<int>(i));
                }
            }
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
    for(auto& obj:shapes) {
        obj->mouseMoveEvent(event);
    }
    selectGroup->mouseMoveEvent(event);

    updateMasterState();
    update();
}

void RenderArea::mouseReleaseEvent(QMouseEvent *event) {
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
    shapes[0]->rotate(3.14159 / 4); //to test
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
