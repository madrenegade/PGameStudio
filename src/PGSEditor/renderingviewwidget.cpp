#include "renderingviewwidget.h"
#include "ui_renderingviewwidget.h"
#include "scene.h"

#include <QtOpenGL/QGLWidget>
#include <QGraphicsProxyWidget>
#include <QDialog>

RenderingViewWidget::RenderingViewWidget(EditorApplication* app, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RenderingViewWidget), app(app)
{
    ui->setupUi(this);

    auto scene = new Scene(app);
    ui->graphicsView->setScene(scene);

    glWidget = new QGLWidget(QGLFormat(QGL::SampleBuffers | QGL::Rgba));
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

