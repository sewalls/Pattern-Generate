#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QMenuBar>
#include "renderarea.h"

//QT_BEGIN_NAMESPACE
//class QComboBox;
//QT_END_NAMESPACE

class Window : public QWidget
{
    Q_OBJECT

public:
    Window();
    void addAction(const char *slot, QString actionName, QActionGroup *actionGroup, bool canCheck);

private:
    RenderArea *renderArea;
    QMenuBar *menuBar;
    QMenu *chooseMenu;
    QAction *menuAction;
};

#endif // WINDOW_H
