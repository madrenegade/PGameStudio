#include "newscenewizard.h"
#include "ui_newscenewizard.h"

NewSceneWizard::NewSceneWizard(QWidget *parent) :
    QWizard(parent),
    ui(new Ui::Wizard)
{
    ui->setupUi(this);
}

NewSceneWizard::~NewSceneWizard()
{
    delete ui;
}
