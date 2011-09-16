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

QStringList NewSceneWizard::selectedSystems() const
{
    QStringList selectedSystems;

    if(ui->checkBoxAI->isChecked())
    {
        selectedSystems.push_back("AI");
    }

    if(ui->checkBoxAtmosphere->isChecked())
    {
        selectedSystems.push_back("Atmosphere");
    }

    if(ui->checkBoxGeometry->isChecked())
    {
        selectedSystems.push_back("Geometry");
    }

    if(ui->checkBoxGraphics->isChecked())
    {
        selectedSystems.push_back("Graphics");
    }

    if(ui->checkBoxGUI->isChecked())
    {
        selectedSystems.push_back("GUI");
    }

    if(ui->checkBoxInput->isChecked())
    {
        selectedSystems.push_back("Input");
    }

    if(ui->checkBoxParticles->isChecked())
    {
        selectedSystems.push_back("Particles");
    }

    if(ui->checkBoxPhysics->isChecked())
    {
        selectedSystems.push_back("Physics");
    }

    if(ui->checkBoxSound->isChecked())
    {
        selectedSystems.push_back("Sound");
    }

    if(ui->checkBoxTerrain->isChecked())
    {
        selectedSystems.push_back("Terrain");
    }

    return selectedSystems;
}
