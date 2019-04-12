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
    QActionGroup *tileBar  = new QActionGroup(this);

    chooseMenu = menuBar->addMenu("Shape");
    addAction(SLOT(ellipseTrigger()), "Ellipse", shapeBar, true);
    addAction(SLOT(rectangleTrigger()), "Rectangle", shapeBar, true);
    addAction(SLOT(lineTrigger()), "Line", shapeBar, true);
    addAction(SLOT(polygonTrigger()), "Polygon", shapeBar, true);
    addAction(SLOT(selectTrigger()), "Select", shapeBar, true);

    chooseMenu = menuBar->addMenu("Color");
    addAction(SLOT(colorPenOpened()), "Choose Outline Color", colorBar, false);
    addAction(SLOT(colorBrushOpened()), "Choose Fill Color", colorBar, false);

    chooseMenu = menuBar->addMenu("Group");
    addAction(SLOT(disbandGroup()), "Delete Group", groupBar, false);

    chooseMenu = menuBar->addMenu("Tile");
    addAction(SLOT(tileStart()), "Tile", tileBar, false);

    this->layout()->setMenuBar(menuBar);
    this->setStyleSheet("background-color: white;");
    setWindowTitle(tr("Draw"));
    setFixedSize(1600, 900);
}

void Window::addAction(const char* slot, QString actionName, QActionGroup *actionGroup, bool canCheck) {
    menuAction = chooseMenu->addAction(actionName);
    menuAction->setCheckable(canCheck);
    actionGroup->addAction(menuAction);
    connect(menuAction, SIGNAL(triggered()), renderArea, slot);
}


