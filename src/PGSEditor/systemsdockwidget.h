#ifndef SYSTEMSDOCKWIDGET_H
#define SYSTEMSDOCKWIDGET_H

#include <QDockWidget>

namespace Ui {
    class SystemsDockWidget;
}

class Controller;

class SystemsDockWidget : public QDockWidget
{
    Q_OBJECT

public:
    explicit SystemsDockWidget(Controller* controller, QWidget *parent = 0);
    ~SystemsDockWidget();

private:
    Ui::SystemsDockWidget *ui;

    Controller* controller;

    QWidget* createSystemTab(const QString& system);
};

#endif // SYSTEMSDOCKWIDGET_H
