#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "memprof/server.h"
#include <QtConcurrentRun>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), aboutDialog(new AboutDialog(this)), server(new memprof::server)
{
    ui->setupUi(this);

    QObject::connect(ui->actionAbout, SIGNAL(activated()),
                     this, SLOT(openAboutDialog()));

    serverThread = new ServerThread(server);
    serverThread->start();
}

MainWindow::~MainWindow()
{
    serverThread->wait(1000);
    serverThread->exit(1);

    delete server;

    delete serverThread;
    delete ui;
}

void MainWindow::openAboutDialog() const
{
    aboutDialog->show();
}
