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

#include <QPainter>
#include <QPaintEvent>

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
void RenderArea::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing);
    //    painter.fillRect(event->rect(), QBrush(Qt::white));


    //    painter.translate(66, 66);
    //! [5]

    //! [6]
    painter.save();                 //saves painter state, because following functions might change it
    //    transformPainter(painter);
    drawShape(painter);
    painter.restore();
    //! [6]

    //! [7]
    drawOutline(painter);
    //! [7]

    //! [8]
    transformPainter(painter);

    if(activeShape) {
        activeShape->changePen(penSelected);   //default shape?
    }

    for(unsigned int i = 0; i < shapes.size(); i++) {
        shapes[i]->draw(&painter);
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
    if (event->button() == Qt::LeftButton) {
        switch(shapeSelected) {
        case Ellipse: {
            class Ellipse* cr = new class Ellipse();
            cr->mousePressEvent(event);
            shapes.push_back(cr);
            activeShape = cr;
            break;
        }
        case LineShape: {
            class Line* ln = new class Line();
            ln->mousePressEvent(event);
            shapes.push_back(ln);
            activeShape = ln;
            break;
        }
        case Rectangle: {
            class Rectangle* rc = new class Rectangle();
            rc->mousePressEvent(event);
            shapes.push_back(rc);
            activeShape = rc;
            break;
        }
        case FreeDraw: {
            class FreeDraw* fd = new class FreeDraw();
            fd->mousePressEvent(event);
            shapes.push_back(fd);
            activeShape = fd;
            break;
        }
        case Select: {
            if(activeShape) {
                shapes[0]->mousePressEventSelect(event);
                for(unsigned int i = 1; i < shapes.size(); i++) {
                    if(!shapes[i-1]->isMoving) {
                        shapes[i]->mousePressEventSelect(event);
                    }
                }
            }
        }
        }
    }
}

void RenderArea::mouseMoveEvent(QMouseEvent *event) {
    if(activeShape) {
        if(shapeSelected == shapeSelect::Select) {
            shapes[0]->mouseMoveEventSelect(event);
            for(unsigned int i = 1; i < shapes.size(); i++) {
                if(!shapes[i-1]->isMoving) {
                    shapes[i]->mouseMoveEventSelect(event);
                }
            }
        }
        else {
            activeShape->mouseMoveEvent(event);
        }
        update();
    }
}

void RenderArea::mouseReleaseEvent(QMouseEvent *event) {
    if(activeShape) {
        if(shapeSelected == shapeSelect::Select) {
            shapes[0]->mouseReleaseEventSelect(event);
            for(unsigned int i = 1; i < shapes.size(); i++) {
                if(!shapes[i-1]->isMoving) {
                    shapes[i]->mouseReleaseEventSelect(event);
                }
            }
        }
        else {
            activeShape->mouseReleaseEvent(event);
        }
        update();
    }
}

void RenderArea::keyPressEvent(QKeyEvent *event) {
    if(event->key() == Qt::Key_E) { //if needed

    }
}
