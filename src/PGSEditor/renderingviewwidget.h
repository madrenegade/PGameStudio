#ifndef RENDERINGVIEWWIDGET_H
#define RENDERINGVIEWWIDGET_H

#include <QWidget>
#include <QGLWidget>
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

    QGLWidget* getGLWidget()
    {
        return glWidget;
    }

private:
    Ui::RenderingViewWidget *ui;

    EditorApplication* app;
    QComboBox* possibleViews;

    QGLWidget* glWidget;
};

#endif // RENDERINGVIEWWIDGET_H
