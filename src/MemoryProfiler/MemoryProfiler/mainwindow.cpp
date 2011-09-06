#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "memprof/server.h"
#include <QtConcurrentRun>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), aboutDialog(new AboutDialog(this))
{
    ui->setupUi(this);

    QObject::connect(ui->actionAbout, SIGNAL(activated()),
                     this, SLOT(openAboutDialog()));

    serverThread = new ServerThread;
    serverThread->start();
}

MainWindow::~MainWindow()
{
    serverThread->exit();

    delete serverThread;
    delete ui;
}

void MainWindow::openAboutDialog() const
{
    aboutDialog->show();
}
