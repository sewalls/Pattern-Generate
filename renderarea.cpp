/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "renderarea.h"
#include "ellipse.h"
#include "line.h"           //better way to include?
#include "rectangle.h"
#include "freedraw.h"
#include "polyline.h"

#include <QPainter>
#include <QPaintEvent>  //todo: sizeable grid / margins

//! [0]
RenderArea::RenderArea(QWidget *parent)
    : QWidget(parent)
{
    QFont newFont = font();
    newFont.setPixelSize(12);
    setFont(newFont);
    activeShape = nullptr;

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
    //    painter.fillRect(event->rect(), QBrush(Qt::white));

    for(unsigned int i = 0; i < shapes.size(); i++) {
        if(shapes[i] != activeShape) {
            shapes[i]->draw(&painter);
        }
    }

    if(activeShape) { //revise this
        activeShape->drawSelected(&painter);
    }

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
        if(activeShape == shapes[i]) {
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
        case LineShape: {
            if(masterState == Finished) {
                class Line* ln = new class Line();
                shapes.push_back(ln);
                ln->changePen(pen);
                activeShape = ln;
            }
            break;
        }
        case Rectangle: {
            if(masterState == Finished) {
                class Rectangle* rc = new class Rectangle();
                shapes.push_back(rc);
                rc->changePen(pen);
                rc->changeBrush(brush);
                activeShape = rc;
            }
            break;
        }
        case FreeDraw: {
            if(masterState == Finished) {
                class FreeDraw* fd = new class FreeDraw();
                shapes.push_back(fd);
                fd->changePen(pen);
                activeShape = fd;
            }
            break;
        }
        case Ellipse: {
            if(masterState == Finished) {
                class Ellipse* el = new class Ellipse();
                shapes.push_back(el);
                el->changePen(pen);
                el->changeBrush(brush);
                activeShape = el;
            }
            break;
        }
        case PolyLine: {
            if(masterState == Finished) {
                class PolyLine* pl = new class PolyLine();
                shapes.push_back(pl);
                pl->changePen(pen);
                pl->changeBrush(brush);
                activeShape = pl;
            }
            break;
        }

        case Select: {
            if(anyShapeClicked(event)) {
                for(unsigned int i = 0; i < shapes.size(); i++) {
                    if(shapes[i]->isClickedOn(event)) {
                        setActiveShape(shapes[i]);
                    }
                }

                activeShape->currentState = Moving;
                shapes.push_back(activeShape);

                for(unsigned int i = 0; i < shapes.size() - 1; i++) {
                    if(activeShape == shapes[i]) {
                        shapes.erase(shapes.begin() + i);
                    }
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
    if(event->key() == Qt::Key_E) { //broken
        masterState = Finished;
    }
    if(event->key() == Qt::Key_C) {
        shapes.clear();
    }
}

void RenderArea::colorPenOpened() {           //todo: set it to update asap
    QColorDialog options;
    options.setOption(QColorDialog::ShowAlphaChannel);
    brush.setColor(colorDialog.getColor(Qt::black, this, "Pick a Pen Color", options.options()));  //theres certainly a better way to do this
    if(activeShape) {
        activeShape->changePen(pen);
    }
}

void RenderArea::colorBrushOpened() {           //todo: set it to update asap
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
