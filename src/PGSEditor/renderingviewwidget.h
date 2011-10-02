#ifndef RENDERINGVIEWWIDGET_H
#define RENDERINGVIEWWIDGET_H

#include <QWidget>
#include <QComboBox>

namespace Ui {
    class RenderingViewWidget;
}

class EditorApplication;

class RenderingViewWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RenderingViewWidget(EditorApplication* app, QWidget *parent);
    ~RenderingViewWidget();

private:
    Ui::RenderingViewWidget *ui;

    EditorApplication* app;
    QComboBox* possibleViews;
};

#endif // RENDERINGVIEWWIDGET_H
