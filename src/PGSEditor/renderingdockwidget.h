#ifndef RENDERINGDOCKWIDGET_H
#define RENDERINGDOCKWIDGET_H

#include <QDockWidget>

namespace Ui {
    class RenderingDockWidget;
}

class RenderingDockWidget : public QDockWidget
{
    Q_OBJECT

public:
    explicit RenderingDockWidget(QWidget *parent = 0);
    ~RenderingDockWidget();

private:
    Ui::RenderingDockWidget *ui;
};

#endif // RENDERINGDOCKWIDGET_H
