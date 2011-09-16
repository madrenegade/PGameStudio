#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "controller.h"

#include "systemsdockwidget.h"
#include "renderingdockwidget.h"
#include "singleviewwidget.h"
#include "multiviewwidget.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow), controller(new Controller(this))
{
    ui->setupUi(this);

    viewWidget = new SingleViewWidget(this);
    ui->centralWidget->layout()->addWidget(viewWidget);

    addDockWidget(Qt::LeftDockWidgetArea, new SystemsDockWidget(controller, this));
    addDockWidget(Qt::LeftDockWidgetArea, new RenderingDockWidget(controller, this));

    ui->mainToolBar->addAction(QIcon::fromTheme("run"), "Run", controller, SLOT(onRun()));

    connect(ui->actionNew_Scene, SIGNAL(triggered()), controller, SLOT(onNewScene()));
    connect(ui->actionImport, SIGNAL(triggered()), controller, SLOT(onImportAsset()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onSceneChanged()
{
    QMessageBox::information(this, "Not implemented", "This feature is not yet implemented", QMessageBox::Close);
}

void MainWindow::onAssetImported()
{
    QMessageBox::information(this, "Not implemented", "This feature is not yet implemented", QMessageBox::Close);
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
