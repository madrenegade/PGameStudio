#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "controller.h"

#include "systemsdockwidget.h"
#include "renderingdockwidget.h"
#include "singleviewwidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow), controller(new Controller(this))
{
    ui->setupUi(this);

    ui->centralWidget->layout()->addWidget(new SingleViewWidget(this));

    addDockWidget(Qt::LeftDockWidgetArea, new SystemsDockWidget(controller, this));
    addDockWidget(Qt::LeftDockWidgetArea, new RenderingDockWidget(controller, this));

    connect(ui->actionNew_Scene, SIGNAL(triggered()), controller, SLOT(onNewScene()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
