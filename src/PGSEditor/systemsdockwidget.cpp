#include "systemsdockwidget.h"
#include "ui_systemsdockwidget.h"
#include "controller.h"

#include <QLabel>

SystemsDockWidget::SystemsDockWidget(Controller* controller, QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::SystemsDockWidget), controller(controller)
{
    ui->setupUi(this);

    auto availableSystems(controller->availableSystems());

    for(auto i = availableSystems.begin(); i != availableSystems.end(); ++i)
    {
        ui->tabWidget->addTab(createSystemTab(*i), *i);
    }
}

SystemsDockWidget::~SystemsDockWidget()
{
    delete ui;
}

QWidget* SystemsDockWidget::createSystemTab(const QString& system)
{
    return new QLabel("Example setting for " + system, this);
}
