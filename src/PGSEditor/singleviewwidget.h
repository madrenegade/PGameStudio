#ifndef SINGLEVIEWWIDGET_H
#define SINGLEVIEWWIDGET_H

#include <QWidget>
#include <QGLWidget>

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

    QGLWidget* getGLWidget()
    {
        return glWidget;
    }

private:
    Ui::SingleViewWidget *ui;

    QGLWidget* glWidget;
};

#endif // SINGLEVIEWWIDGET_H
