#ifndef SYSTEMSDOCKWIDGET_H
#define SYSTEMSDOCKWIDGET_H

#include <QDockWidget>

namespace Ui {
    class SystemsDockWidget;
}

class SystemsDockWidget : public QDockWidget
{
    Q_OBJECT

public:
    explicit SystemsDockWidget(QWidget *parent = 0);
    ~SystemsDockWidget();

private:
    Ui::SystemsDockWidget *ui;
};

#endif // SYSTEMSDOCKWIDGET_H
