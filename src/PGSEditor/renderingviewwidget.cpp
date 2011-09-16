#include "renderingviewwidget.h"
#include "ui_renderingviewwidget.h"
#include "scene.h"

#include <QtOpenGL/QGLWidget>
#include <QGraphicsProxyWidget>
#include <QDialog>

RenderingViewWidget::RenderingViewWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RenderingViewWidget)
{
    ui->setupUi(this);


    auto scene = new Scene();
    ui->graphicsView->setScene(scene);

    auto glWidget = new QGLWidget(QGLFormat(QGL::SampleBuffers | QGL::Rgba));
    ui->graphicsView->setViewport(glWidget);

//    possibleViews = new QComboBox();
//    possibleViews->addItem("3D");
//    possibleViews->addItem("Top");
//    possibleViews->addItem("Bottom");
//    possibleViews->addItem("Left");
//    possibleViews->addItem("Right");

//    QGraphicsProxyWidget* proxy = scene->addWidget(possibleViews);
//    proxy->setPos(500, 100);
    //proxy->setZValue(1);
}

RenderingViewWidget::~RenderingViewWidget()
{
    delete ui;
}
