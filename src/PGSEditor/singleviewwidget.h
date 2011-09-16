#ifndef SINGLEVIEWWIDGET_H
#define SINGLEVIEWWIDGET_H

#include <QWidget>

namespace Ui {
    class SingleViewWidget;
}

class SingleViewWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SingleViewWidget(QWidget *parent = 0);
    ~SingleViewWidget();

private:
    Ui::SingleViewWidget *ui;
};

#endif // SINGLEVIEWWIDGET_H
