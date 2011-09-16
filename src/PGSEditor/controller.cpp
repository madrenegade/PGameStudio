#include "controller.h"
#include "sceneexporter.h"

#include <QDebug>
#include <QFileDialog>

Controller::Controller(MainWindow* mainWindow)
    : QWidget(mainWindow), mainWindow(mainWindow),
      newSceneWizard(new NewSceneWizard(this))
{
    connect(newSceneWizard, SIGNAL(accepted()), this, SLOT(onNewSceneConfigured()));
    connect(this, SIGNAL(sceneDirectorySelected(const QString&)), this, SLOT(onSaveNewScene(const QString&)));
}

QStringList Controller::availableSystems() const
{
    QStringList availableSystems;
    availableSystems.push_back("AI");
    availableSystems.push_back("Atmosphere");
    availableSystems.push_back("Geometry");
    availableSystems.push_back("Graphics");
    availableSystems.push_back("GUI");
    availableSystems.push_back("Input");
    availableSystems.push_back("Particles");
    availableSystems.push_back("Physics");
    availableSystems.push_back("Sound");
    availableSystems.push_back("Terrain");

    return availableSystems;
}

void Controller::onNewScene()
{
    newSceneWizard->restart();
    newSceneWizard->show();
}

void Controller::onNewSceneConfigured()
{
    QString dir = QFileDialog::getExistingDirectory(this);

    sceneDirectorySelected(dir);
}

void Controller::onSaveNewScene(const QString& dir)
{
    QStringList selectedSystems(newSceneWizard->selectedSystems());

    SceneExporter exporter;
    exporter.createEmptyScene(dir, selectedSystems);
}
