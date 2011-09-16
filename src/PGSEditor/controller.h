#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "mainwindow.h"
#include "newscenewizard.h"

#include <boost/scoped_ptr.hpp>

class Controller : public QWidget
{
    Q_OBJECT
public:
    explicit Controller(MainWindow* mainWindow);

    QStringList availableSystems() const;

signals:
    void sceneDirectorySelected(const QString& dir);

public slots:
    void onNewScene();
    void onNewSceneConfigured();
    void onSaveNewScene(const QString& dir);

private:
    MainWindow* mainWindow;

    NewSceneWizard* newSceneWizard;
};

#endif // CONTROLLER_H
