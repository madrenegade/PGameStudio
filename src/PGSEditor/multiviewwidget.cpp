#include "multiviewwidget.h"
#include "ui_multiviewwidget.h"

#include "renderingviewwidget.h"

MultiViewWidget::MultiViewWidget(EditorApplication* app, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MultiViewWidget)
{
    ui->setupUi(this);

    ui->gridLayout->addWidget(new RenderingViewWidget(app, this), 0, 0);
    ui->gridLayout->addWidget(new RenderingViewWidget(app, this), 0, 1);
    ui->gridLayout->addWidget(new RenderingViewWidget(app, this), 1, 0);
    ui->gridLayout->addWidget(new RenderingViewWidget(app, this), 1, 1);
}

MultiViewWidget::~MultiViewWidget()
{
    delete ui;
}
