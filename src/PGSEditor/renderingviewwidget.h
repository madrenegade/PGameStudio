#ifndef RENDERINGVIEWWIDGET_H
#define RENDERINGVIEWWIDGET_H

#include <QWidget>
#include <QComboBox>

namespace Ui {
    class RenderingViewWidget;
}

class RenderingViewWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RenderingViewWidget(QWidget *parent = 0);
    ~RenderingViewWidget();


private:
    Ui::RenderingViewWidget *ui;

    QComboBox* possibleViews;
};

#endif // RENDERINGVIEWWIDGET_H
