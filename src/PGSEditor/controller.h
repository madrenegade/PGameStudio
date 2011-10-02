#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "mainwindow.h"
#include "newscenewizard.h"
#include "assetimportwizard.h"

#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>

class SceneData;
class Material;
class EditorApplication;

class Controller : public QWidget
{
    Q_OBJECT
public:
    explicit Controller(MainWindow* mainWindow);
    virtual ~Controller();

    EditorApplication* getEditorApplication();

    QStringList availableSystems() const;
    QStringList getAssetImportPostProcessingSteps() const;

    SceneData* getSceneData() const;

    Material* getMaterial(const QString& name) const;

signals:
    void sceneDirectorySelected(const QString& dir);
    void sceneChanged();

public slots:
    void onNewScene();
    void onNewSceneConfigured();
    void onSaveNewScene(const QString& dir);

    void onImportAsset();
    void onImportConfigured();

    void onRun();

    void onExport();

private:
    MainWindow* mainWindow;

    NewSceneWizard* newSceneWizard;
    AssetImportWizard* assetImportWizard;

    boost::shared_ptr<EditorApplication> editorApplication;

    boost::shared_ptr<SceneData> currentScene;
};

#endif // CONTROLLER_H
