#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "mainwindow.h"
#include "newscenewizard.h"
#include "assetimportwizard.h"

#include <boost/scoped_ptr.hpp>

class Controller : public QWidget
{
    Q_OBJECT
public:
    explicit Controller(MainWindow* mainWindow);

    QStringList availableSystems() const;

signals:
    void sceneDirectorySelected(const QString& dir);
    void sceneChanged();

    void assetImported();

public slots:
    void onNewScene();
    void onNewSceneConfigured();
    void onSaveNewScene(const QString& dir);

    void onImportAsset();
    void onImportConfigured();

    void onRun();

private:
    MainWindow* mainWindow;

    NewSceneWizard* newSceneWizard;
    AssetImportWizard* assetImportWizard;
};

#endif // CONTROLLER_H
