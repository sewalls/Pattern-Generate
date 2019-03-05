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

#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QList>
#include <QPainterPath>
#include <QRect>
#include <QWidget>
#include <QMouseEvent>
#include <QKeyEvent>
#include <vector>
#include <QColorDialog>
#include "shape.h"
#include "vec2d.h"

QT_BEGIN_NAMESPACE
class QPaintEvent;
QT_END_NAMESPACE

//! [0]
enum Operation { NoTransformation, Translate, Rotate, Scale };
enum shapeSelect { Ellipse, LineShape, Rectangle, FreeDraw, PolyLine, Select };
//! [0]

//! [1]
class RenderArea : public QWidget
{
    Q_OBJECT

public:
    RenderArea(QWidget *parent = 0);

    void setOperations(const QList<Operation> &operations);
    void setShape(const QPainterPath &shape);

    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
//! [1]

public slots:
    void ellipseTrigger() { shapeSelected = shapeSelect::Ellipse; }
    void rectangleTrigger() { shapeSelected = shapeSelect::Rectangle; }
    void lineTrigger() { shapeSelected = shapeSelect::LineShape; }
    void freedrawTrigger() { shapeSelected = shapeSelect::FreeDraw; }
    void polyTrigger() { shapeSelected = shapeSelect::PolyLine; }
    void selectTrigger() { shapeSelected = shapeSelect::Select; }
    void solidTrigger() { pen.setStyle(Qt::SolidLine); selectMode = false; }
    void dashedTrigger() { pen.setStyle(Qt::DashLine); selectMode = false; } //freedraw line is not working properly
    void dottedTrigger()  { pen.setStyle(Qt::DotLine); selectMode = false; }
    void colorOpened();

//! [2]
private:
    void drawCoordinates(QPainter &painter);
    void drawOutline(QPainter &painter);
    void drawShape(QPainter &painter);
    void transformPainter(QPainter &painter);
    void setActiveShape(Shape *active);

    QList<Operation> operations;
    QPainterPath shape;
    QRect xBoundingRect;
    QRect yBoundingRect;
    std::vector<Shape*> shapes;
    shapeSelect shapeSelected;
    QPen pen;
    Shape* activeShape; //fix drawing
    bool selectMode;
    QColorDialog colorDialog;
    State masterState = Finished;
};
//! [2]

#endif // RENDERAREA_H
