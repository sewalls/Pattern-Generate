#include "renderarea.h"
#include "ellipse.h"
#include "line.h"           //better way to include?
#include "rectangle.h"
#include "freedraw.h"
#include "polyline.h"
#include "group.h"

#include <QPainter>
#include <QPaintEvent>  //todo: sizeable grid / margins
#include <algorithm>

//! [0]
RenderArea::RenderArea(QWidget *parent)
    : QWidget(parent), selectGroup{new Group}
{
    QFont newFont = font();
    newFont.setPixelSize(12);
    setFont(newFont);
    activeShape = nullptr;

    setFocusPolicy(Qt::StrongFocus);
    setFocus();

    QFontMetrics fontMetrics(newFont);
    xBoundingRect = fontMetrics.boundingRect(tr("x"));
    yBoundingRect = fontMetrics.boundingRect(tr("y"));
    pen.setColor(Qt::black);
    brush.setColor(Qt::transparent);
}
//! [0]

//! [1]
void RenderArea::setOperations(const QList<Operation> &operations)
{
    this->operations = operations;
    update();
}
//! [1]

//! [2]
void RenderArea::setShape(const QPainterPath &shape)
{
    this->shape = shape;
    update();
}
//! [2]

//! [3]
QSize RenderArea::minimumSizeHint() const
{
    return QSize(182, 182);
}
//! [3]

//! [4]
QSize RenderArea::sizeHint() const
{
    return QSize(232, 232);
}
//! [4]

//! [5]
void RenderArea::paintEvent(__attribute__((unused))QPaintEvent *event) //currently marked unused to silence warnings
{
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing);
    painter.drawRect(550, 350, 200, 200);
    //    painter.fillRect(event->rect(), QBrush(Qt::white));

    //    for(unsigned int i = 0; i < shapes.size(); i++) {
    //        if(shapes[i] != activeShape) {
    //            shapes[i]->pen.setStyle(Qt::SolidLine);
    //            shapes[i]->draw(&painter);
    //        }
    //    }

    //    if(activeShape) { //revise this
    //        activeShape->pen.setStyle(Qt::DotLine);
    //        activeShape->draw(&painter);
    //    }

    for(unsigned int i = 0; i < shapes.size(); i++) {
        shapes[i]->draw(&painter);
    }
    selectGroup->draw(&painter);

    drawTiles(painter);

    switch(masterState) { //for testing
    case Precreated: {
        painter.drawText(10, 10, "P");
        break;
    }
    case Creating: {
        painter.drawText(10, 10, "C");
        break;
    }
    case Moving: {
        painter.drawText(10, 10, "M");
        break;
    }
    case Finished: {
        painter.drawText(10, 10, "F");
        break;
    }
    }

    for(unsigned int i = 0; i < shapes.size(); i++) {
        if(activeShape == shapes[i].get()) {
            painter.drawText(20, 10, QString::fromStdString(std::to_string(i)));
        }
    }
}
//! [8]

//! [10]
void RenderArea::drawOutline(QPainter &painter)
{
    painter.setPen(Qt::black);
    painter.setPen(Qt::SolidLine);
    painter.setBrush(Qt::NoBrush);
}
//! [10]

//! [11]
void RenderArea::drawShape(QPainter &painter)
{
    painter.fillPath(shape, Qt::blue);
}
//! [11]

//! [12]
void RenderArea::transformPainter(QPainter &painter)
{
    for (int i = 0; i < operations.size(); ++i) {
        switch (operations[i]) {
        case Translate:
            painter.translate(50, 50);
            break;
        case Scale:
            painter.scale(0.75, 0.75);
            break;
        case Rotate:
            painter.rotate(60);
            break;
        case NoTransformation:
            ;
        }
    }
}
//! [12]

void RenderArea::mousePressEvent(QMouseEvent *event) {
    if(event->button() == Qt::LeftButton) {
        switch(shapeSelected) {
        case shapeSelect::Line: {
            if(masterState == Finished) {
                addShape<Line>();
            }
            break;
        }
        case shapeSelect::Rectangle: {
            if(masterState == Finished) {
                addShape<Rectangle>();
            }
            break;
        }
        case shapeSelect::FreeDraw: {
            if(masterState == Finished) {
                addShape<FreeDraw>();
            }
            break;
        }
        case shapeSelect::Ellipse: {
            if(masterState == Finished) {
                addShape<Ellipse>();
            }
            break;
        }
        case shapeSelect::PolyLine: {
            if(masterState == Finished) {
                addShape<PolyLine>();
            }
            break;
        }

        case shapeSelect::Select: {
            if(anyShapeClicked(event)) {
                if(event->modifiers() == Qt::ShiftModifier) {
                    setActiveShape(selectGroup.get());
                    for(unsigned int i = 0; i < shapes.size(); i++) {
                        if(shapes[i]->isClickedOn(event)) {
                            selectGroup->childShapes.push_back(std::move(shapes[i]));
                            shapes.erase(shapes.begin() + i);
                        }
                    }
                }
                //perhaps I could arrange this better, the if else may not be necessary
                else {
                    for(unsigned int i = 0; i < shapes.size(); i++) {
                        if(shapes[i]->isClickedOn(event)) {
                            setActiveShape(shapes[i].get());
                        }
                    }
                }

                if(activeShape) {
                    activeShape->currentState = Moving;
                }
            }
            else {
                activeShape = nullptr;
            }
        }
        }

        for(int i = static_cast<int>(shapes.size()) - 1; i >= 0; i--) { //weird casting to avoid warnings
            shapes[static_cast<unsigned int>(i)]->mousePressEvent(event);
        }

        if(activeShape) {
            masterState = activeShape->currentState;
        }
    }
    update();
}

void RenderArea::mouseMoveEvent(QMouseEvent *event) {
    for(int i = static_cast<int>(shapes.size()) - 1; i >= 0; i--) { //weird casting to avoid warnings
        shapes[static_cast<unsigned int>(i)]->mouseMoveEvent(event);
    }
    if(activeShape) {
        masterState = activeShape->currentState;
    }
    update();
}

void RenderArea::mouseReleaseEvent(QMouseEvent *event) {
    for(int i = static_cast<int>(shapes.size()) - 1; i >= 0; i--) { //weird casting to avoid warnings
        shapes[static_cast<unsigned int>(i)]->mouseReleaseEvent(event);
    }
    if(activeShape) {
        masterState = activeShape->currentState;
    }
    update();
}

void RenderArea::keyPressEvent(QKeyEvent *event) {
    if(event->key() == Qt::Key_E) {
        masterState = Finished;
    }
    if(event->key() == Qt::Key_C) {
        shapes.clear();
        update();
    }
}

void RenderArea::colorPenOpened() {
    QColorDialog options;
    options.setOption(QColorDialog::ShowAlphaChannel);
    pen.setColor(colorDialog.getColor(Qt::black, this, "Pick a Pen Color", options.options()));  //theres certainly a better way to do this
    if(activeShape) {
        activeShape->changePen(pen);
    }
}

void RenderArea::colorBrushOpened() {
    QColorDialog options;
    options.setOption(QColorDialog::ShowAlphaChannel);
    brush.setColor(colorDialog.getColor(Qt::white, this, "Pick a Fill Color", options.options()));
    if(activeShape) {
        activeShape->changeBrush(brush);
    }
}

void RenderArea::setActiveShape(Shape* active) {
    if(activeShape != active) {
        if(activeShape) {
            activeShape->currentState = Finished;
        }
        activeShape = active;
    }
}

bool RenderArea::anyShapeClicked(QMouseEvent *event) {
    bool anyClicked = false;
    for(unsigned int i = 0; i < shapes.size(); i++) {
        if(shapes[i]->isClickedOn(event)) {
            anyClicked = true;
        }
    }
    return anyClicked;
}

void RenderArea::drawTiles(QPainter &painter) {
    for(unsigned int i = 0; i < shapes.size(); i++) {

    }
}

template<typename T>
T* RenderArea::addShape() {
    std::unique_ptr<Shape> shape{new T};
    shape->changePen(pen);
    shape->changeBrush(brush);
    activeShape = shape.get();
    activeShape->order = shapes.size();
    shapes.push_back(std::move(shape));
    return static_cast<T*>(activeShape);
}
