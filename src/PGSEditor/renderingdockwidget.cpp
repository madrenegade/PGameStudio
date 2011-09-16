#include "renderingdockwidget.h"
#include "ui_renderingdockwidget.h"

RenderingDockWidget::RenderingDockWidget(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::RenderingDockWidget)
{
    ui->setupUi(this);
}

RenderingDockWidget::~RenderingDockWidget()
{
    delete ui;
}
