#include "controller.h"

#include <QDebug>

Controller::Controller(MainWindow* mainWindow)
    : QObject(mainWindow), mainWindow(mainWindow),
      newSceneWizard(new NewSceneWizard())
{
}

void Controller::onNewScene()
{
    newSceneWizard->restart();
    newSceneWizard->show();
}
