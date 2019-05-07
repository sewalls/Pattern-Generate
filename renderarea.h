#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QColorDialog>
#include <QInputDialog>
#include <QGuiApplication>

#include <memory>

#include "shape.h"
#include "rectangle.h"
#include "line.h"
#include "ellipse.h"
#include "polygon.h"
#include "group.h"

enum class ShapeName { Ellipse, Line, Rectangle, Polygon, Select };

class RenderArea : public QWidget
{
    Q_OBJECT

public:
    RenderArea(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

public slots:
    void ellipseTrigger();
    void rectangleTrigger();
    void lineTrigger();
    void polygonTrigger();
    void selectTrigger();
    void colorPenOpened();
    void colorBrushOpened();
    void tileStart();
    void disbandGroup();
    void scalePrompt();
    void bringToFront();
    void bringForward();
    void bringBackward();
    void bringToBack();
    void screenTest();

public: //remake private
    template<typename T>
    T* addShape();

    void setActiveShape(Shape *shape);
    void updateMasterState();
    void shapeToggleTrigger(ShapeName newShape);
    unsigned int activeShapePosition();

    unsigned int masterIndex = 0;

    QPen pen;
    QBrush brush;

    ShapeName shapeToggled;
    State masterState = State::Finished;
    ShapePtrVctr shapes;
    Shape* activeShape = nullptr;
    Rectangle selectBox;
    Rectangle tileBox;
    std::unique_ptr<Group> selectGroup;
};

#endif // RENDERAREA_H
