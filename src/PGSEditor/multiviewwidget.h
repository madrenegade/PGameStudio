#ifndef MULTIVIEWWIDGET_H
#define MULTIVIEWWIDGET_H

#include <QWidget>

namespace Ui {
    class MultiViewWidget;
}

class EditorApplication;

class MultiViewWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MultiViewWidget(EditorApplication* app, QWidget *parent = 0);
    ~MultiViewWidget();

private:
    Ui::MultiViewWidget *ui;
};

#endif // MULTIVIEWWIDGET_H
