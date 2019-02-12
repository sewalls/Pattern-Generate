#ifndef COLORWINDOW_H
#define COLORWINDOW_H

#include <QWidget>
#include <QColorDialog>

class ColorWindow : public QWidget
{
    Q_OBJECT

public:
    ColorWindow();
    QColorDialog dialog;
};

#endif // COLORWINDOW_H
