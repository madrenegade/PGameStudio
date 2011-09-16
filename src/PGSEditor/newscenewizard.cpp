#include "newscenewizard.h"
#include "ui_newscenewizard.h"
#include "controller.h"

#include <QLayout>

NewSceneWizard::NewSceneWizard(Controller* controller, QWidget *parent) :
    QWizard(parent),
    ui(new Ui::Wizard), controller(controller)
{
    ui->setupUi(this);

    auto availableSystems(controller->availableSystems());

    auto page = ui->wizardPageSystems;

    for(auto i = availableSystems.begin(); i != availableSystems.end(); ++i)
    {
        auto checkBox = new QCheckBox(*i, page);
        page->layout()->addWidget(checkBox);
        systemCheckboxes.append(checkBox);
    }
}

NewSceneWizard::~NewSceneWizard()
{
    delete ui;
}

QStringList NewSceneWizard::selectedSystems() const
{
    QStringList selectedSystems;

    return selectedSystems;
}
