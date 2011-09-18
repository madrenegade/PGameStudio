#include "controller.h"
#include "sceneexporter.h"

#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>

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

QStringList Controller::getAssetImportPostProcessingSteps() const
{
    QStringList postProcessingSteps;

    postProcessingSteps.push_back("CalcTangentSpace");
    postProcessingSteps.push_back("JoinIdenticalVertices");
    postProcessingSteps.push_back("MakeLeftHanded");
    postProcessingSteps.push_back("Triangulate");
    postProcessingSteps.push_back("GenNormals");
    postProcessingSteps.push_back("GenSmoothNormals");
    postProcessingSteps.push_back("PreTransformVertices");
    postProcessingSteps.push_back("ValidateDataStructure");
    postProcessingSteps.push_back("ImproveCacheLocality");
    postProcessingSteps.push_back("RemoveRedundantMaterials");
    postProcessingSteps.push_back("FixInfacingNormals");
    postProcessingSteps.push_back("FindInvalidData");
    postProcessingSteps.push_back("GenUVCoords");
    postProcessingSteps.push_back("FindInstances");
    postProcessingSteps.push_back("OptimizeMeshes");
    postProcessingSteps.push_back("CalcTangentSpace");

    return postProcessingSteps;
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

void Controller::onRun()
{
    QMessageBox::information(this, "Not implemented", "This feature is not yet implemented", QMessageBox::Close);
}
