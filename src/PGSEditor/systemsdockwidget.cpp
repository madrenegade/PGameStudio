#include "systemsdockwidget.h"
#include "ui_systemsdockwidget.h"

SystemsDockWidget::SystemsDockWidget(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::SystemsDockWidget)
{
    ui->setupUi(this);
}

SystemsDockWidget::~SystemsDockWidget()
{
    delete ui;
}
