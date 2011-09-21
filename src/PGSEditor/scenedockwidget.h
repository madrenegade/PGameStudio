#ifndef SCENEDOCKWIDGET_H
#define SCENEDOCKWIDGET_H

#include <QDockWidget>
#include <boost/shared_ptr.hpp>

namespace Ui {
    class SceneDockWidget;
}

class Controller;
class SceneNode;
class QTreeWidgetItem;
class QListWidgetItem;
class QGraphicsScene;

class SceneDockWidget : public QDockWidget
{
    Q_OBJECT

public:
    explicit SceneDockWidget(Controller* controller, QWidget *parent = 0);
    ~SceneDockWidget();

public slots:
    void onSceneChanged();

    void onMaterialSelected(QListWidgetItem* item);
    void onTextureSelected(QListWidgetItem* item);

private:
    void rebuildSceneGraph();
    void rebuildMeshList();
    void rebuildMaterialList();
    void rebuildTextureList();

    QTreeWidgetItem* createNodeItem(const boost::shared_ptr<SceneNode>& node);

    Ui::SceneDockWidget *ui;

    Controller* controller;

    QGraphicsScene* materialPreviewScene;
};

#endif // SCENEDOCKWIDGET_H
