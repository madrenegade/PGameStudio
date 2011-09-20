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

    viewWidget = new SingleViewWidget(this);
    ui->centralWidget->layout()->addWidget(viewWidget);

    sceneDock = new SceneDockWidget(controller, this);
    addDockWidget(Qt::LeftDockWidgetArea, sceneDock);
    addDockWidget(Qt::RightDockWidgetArea, new SystemsDockWidget(controller, this));
    addDockWidget(Qt::RightDockWidgetArea, new RenderingDockWidget(controller, this));

    ui->mainToolBar->addAction(QIcon::fromTheme("run"), "Run", controller, SLOT(onRun()));

    connect(ui->actionNew_Scene, SIGNAL(triggered()), controller, SLOT(onNewScene()));
    connect(ui->actionImport, SIGNAL(triggered()), controller, SLOT(onImportAsset()));
    connect(ui->actionExport, SIGNAL(triggered()), controller, SLOT(onExport()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onSceneChanged()
{
}

void MainWindow::onSetSingleView()
{
    ui->centralWidget->layout()->removeWidget(viewWidget);

    viewWidget = new SingleViewWidget(this);
    ui->centralWidget->layout()->addWidget(viewWidget);
}

void MainWindow::onSetMultiView()
{
    ui->centralWidget->layout()->removeWidget(viewWidget);

    viewWidget = new MultiViewWidget(this);
    ui->centralWidget->layout()->addWidget(viewWidget);
}
