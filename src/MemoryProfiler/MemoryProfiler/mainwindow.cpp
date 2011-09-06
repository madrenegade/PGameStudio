#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), aboutDialog(new AboutDialog(this))
{
    ui->setupUi(this);

    QObject::connect(ui->actionAbout, SIGNAL(activated()),
                     this, SLOT(openAboutDialog()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openAboutDialog() const
{
    aboutDialog->show();
}
