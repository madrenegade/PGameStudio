#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "controller.h"

#include "systemsdockwidget.h"
#include "renderingdockwidget.h"
#include "scenedockwidget.h"

#include "singleviewwidget.h"
#include "multiviewwidget.h"

#include <QMessageBox>
#include <QTreeWidget>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow), controller(new Controller(this))
{
    ui->setupUi(this);

    viewWidget = new SingleViewWidget(controller->getEditorApplication(), this);
    ui->centralWidget->layout()->addWidget(viewWidget);

    sceneDock = new SceneDockWidget(controller, this);
    addDockWidget(Qt::LeftDockWidgetArea, sceneDock);
    addDockWidget(Qt::RightDockWidgetArea, new SystemsDockWidget(controller, this));
    addDockWidget(Qt::RightDockWidgetArea, new RenderingDockWidget(controller, this));

    ui->mainToolBar->addAction(QIcon::fromTheme("media-play").pixmap(16), "Run", controller, SLOT(onRun()));

    connect(ui->actionNew_Scene, SIGNAL(triggered()), controller, SLOT(onNewScene()));
    connect(ui->actionImport, SIGNAL(triggered()), controller, SLOT(onImportAsset()));
    connect(ui->actionExport, SIGNAL(triggered()), controller, SLOT(onExport()));

    setWindowState(Qt::WindowMaximized);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QGLWidget* MainWindow::getGLWidget()
{
    return viewWidget->getGLWidget();
}

void MainWindow::onSceneChanged()
{

}

void MainWindow::onSetSingleView()
{
    ui->centralWidget->layout()->removeWidget(viewWidget);

    viewWidget = new SingleViewWidget(controller->getEditorApplication(), this);
    ui->centralWidget->layout()->addWidget(viewWidget);
}

void MainWindow::onSetMultiView()
{
//    ui->centralWidget->layout()->removeWidget(viewWidget);

//    viewWidget = new MultiViewWidget(controller->getEditorApplication(), this);
//    ui->centralWidget->layout()->addWidget(viewWidget);
}
