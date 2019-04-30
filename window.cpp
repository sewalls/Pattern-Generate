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
    addAction(SLOT(ellipseTrigger()), "Ellipse", shapeBar, true);
    addAction(SLOT(rectangleTrigger()), "Rectangle", shapeBar, true);
    addAction(SLOT(lineTrigger()), "Line", shapeBar, true);
    addAction(SLOT(polygonTrigger()), "Polygon", shapeBar, true);
    addAction(SLOT(selectTrigger()), "Select", shapeBar, true);

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

    chooseMenu = menuBar->addMenu("Edit");
    addAction(SLOT(scalePrompt()), "Scale", editBar, false);

    layout()->setMenuBar(menuBar);
    pal.setColor(QPalette::Background, Qt::white);
    setPalette(pal);
    setWindowTitle(tr("Draw"));
    setFixedSize(1600, 900);
}

void Window::addAction(const char* slot, QString actionName, QActionGroup *actionGroup, bool canCheck) {
    menuAction = chooseMenu->addAction(actionName);
    menuAction->setCheckable(canCheck);
    actionGroup->addAction(menuAction);
    connect(menuAction, SIGNAL(triggered()), renderArea, slot);
}

void Window::backgroundTriggered() {
    QColorDialog dialog;
    pal.setColor(QPalette::Background, dialog.getColor(Qt::white, this, "Pick a Color", dialog.options()));
    setPalette(pal);
}


