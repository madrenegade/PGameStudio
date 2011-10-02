#include "singleviewwidget.h"
#include "ui_singleviewwidget.h"

#include "renderingviewwidget.h"

SingleViewWidget::SingleViewWidget(EditorApplication* app, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SingleViewWidget)
{
    ui->setupUi(this);

    ui->horizontalLayout->addWidget(new RenderingViewWidget(app, this));
}

SingleViewWidget::~SingleViewWidget()
{
    delete ui;
}
