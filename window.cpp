#include "window.h"

#include <QComboBox>
#include <QGridLayout>

Window::Window() {
    renderArea = new RenderArea;
    QVBoxLayout *boxLayout = new QVBoxLayout(this);
    boxLayout->addWidget(renderArea, 0, nullptr);

    menuBar = new QMenuBar;
    chooseMenu = new QMenu;
    QActionGroup *shapeBar = new QActionGroup(this);
    QActionGroup *groupBar = new QActionGroup(this);
    QActionGroup *colorBar = new QActionGroup(this);
    QActionGroup *editBar  = new QActionGroup(this);

    chooseMenu = menuBar->addMenu("Shape");
    addAction(SLOT(ellipseTrigger()), "Ellipse", shapeBar, false);
    addAction(SLOT(rectangleTrigger()), "Rectangle", shapeBar, false);
    addAction(SLOT(lineTrigger()), "Line", shapeBar, false);
    addAction(SLOT(polygonTrigger()), "Polygon", shapeBar, false);
    addAction(SLOT(selectTrigger()), "Select", shapeBar, false);

    chooseMenu = menuBar->addMenu("Color");
    addAction(SLOT(colorPenOpened()), "Choose Outline Color", colorBar, false);
    addAction(SLOT(colorBrushOpened()), "Choose Fill Color", colorBar, false);
    menuAction = chooseMenu->addAction("Choose Background Color");
    menuAction->setCheckable(false);
    colorBar->addAction(menuAction);
    connect(menuAction, SIGNAL(triggered()), this, SLOT(backgroundTriggered()));

    chooseMenu = menuBar->addMenu("Group");
    addAction(SLOT(disbandGroup()), "Delete Group", groupBar, false);
    addAction(SLOT(tileStart()), "Tile", groupBar, false);
    addAction(SLOT(screenTest()), "Save Screenshot", groupBar, false);

    chooseMenu = menuBar->addMenu("Edit");
    addAction(SLOT(bringToFront()), "Bring Shape to Front", editBar, false);
    addAction(SLOT(bringForward()), "Bring Shape Forward", editBar, false);
    addAction(SLOT(bringBackward()), "Push Shape Backwards", editBar, false);
    addAction(SLOT(bringToBack()), "Push Shape to Back", editBar, false);

    layout()->setMenuBar(menuBar);
    pal.setColor(QPalette::Background, Qt::white);
    setPalette(pal);
    setWindowTitle(tr("Wallpaper Maker"));
    setFixedSize(1600, 900);
}

void Window::addAction(const char* slot, QString actionName, QActionGroup *actionGroup, bool canCheck) {
    menuAction = chooseMenu->addAction(actionName);
    menuAction->setCheckable(canCheck); //may be redundant now
    actionGroup->addAction(menuAction);
    connect(menuAction, SIGNAL(triggered()), renderArea, slot);
}

void Window::backgroundTriggered() {
    QColorDialog dialog;
    pal.setColor(QPalette::Background, dialog.getColor(Qt::white, this, "Pick a Color", dialog.options()));
    setPalette(pal);
}


