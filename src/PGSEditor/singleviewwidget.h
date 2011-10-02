#ifndef SINGLEVIEWWIDGET_H
#define SINGLEVIEWWIDGET_H

#include <QWidget>

namespace Ui {
    class SingleViewWidget;
}

class EditorApplication;

class SingleViewWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SingleViewWidget(EditorApplication* app, QWidget* parent);
    ~SingleViewWidget();

private:
    Ui::SingleViewWidget *ui;
};

#endif // SINGLEVIEWWIDGET_H
