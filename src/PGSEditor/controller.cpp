#include "controller.h"
#include "sceneexporter.h"

#include <QDebug>
#include <QFileDialog>

Controller::Controller(MainWindow* mainWindow)
    : QWidget(mainWindow), mainWindow(mainWindow),
      newSceneWizard(new NewSceneWizard(this)),
      assetImportWizard(new AssetImportWizard(this))
{
    connect(newSceneWizard, SIGNAL(accepted()), this, SLOT(onNewSceneConfigured()));
    connect(assetImportWizard, SIGNAL(accepted()), this, SLOT(onImportConfigured()));

    connect(this, SIGNAL(sceneDirectorySelected(const QString&)), this, SLOT(onSaveNewScene(const QString&)));
    connect(this, SIGNAL(sceneChanged()), mainWindow, SLOT(onSceneChanged()));

    connect(this, SIGNAL(assetImported()), mainWindow, SLOT(onAssetImported()));
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

    sceneChanged();
}

void Controller::onImportAsset()
{
    assetImportWizard->restart();
    assetImportWizard->show();
}

void Controller::onImportConfigured()
{
    assetImported();
}
