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

    SceneExporert exporter;
    exporter.createEmptyScene(dir, selectedSystems);
}
