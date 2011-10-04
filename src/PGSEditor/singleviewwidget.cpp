#include "singleviewwidget.h"
#include "ui_singleviewwidget.h"

#include "renderingviewwidget.h"

SingleViewWidget::SingleViewWidget(EditorApplication* app, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SingleViewWidget)
{
    ui->setupUi(this);

    auto renderingWidget = new RenderingViewWidget(app, this);
    glWidget = renderingWidget->getGLWidget();

    ui->horizontalLayout->addWidget(renderingWidget);
}

SingleViewWidget::~SingleViewWidget()
{
    delete ui;
}
