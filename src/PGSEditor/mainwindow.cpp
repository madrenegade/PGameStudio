#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "controller.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), controller(new Controller(this)),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->actionNew_Scene, SIGNAL(triggered()), controller, SLOT(onNewScene()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
