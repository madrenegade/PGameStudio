#ifndef RENDERINGDOCKWIDGET_H
#define RENDERINGDOCKWIDGET_H

#include <QDockWidget>
#include <QCheckBox>

namespace Ui {
    class RenderingDockWidget;
}

class Controller;

class RenderingDockWidget : public QDockWidget
{
    Q_OBJECT

public:
    explicit RenderingDockWidget(Controller* controller, QWidget *parent = 0);
    ~RenderingDockWidget();

private:
    Ui::RenderingDockWidget *ui;

    Controller* controller;

    QList<QCheckBox*> debugDrawingCheckBoxes;
};

#endif // RENDERINGDOCKWIDGET_H
