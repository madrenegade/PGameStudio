#include "scenedockwidget.h"
#include "ui_scenedockwidget.h"
#include "controller.h"
#include "scenedata.h"
#include "scenenode.h"
#include "mesh.h"

SceneDockWidget::SceneDockWidget(Controller* controller, QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::SceneDockWidget), controller(controller)
{
    ui->setupUi(this);

    connect(controller, SIGNAL(sceneChanged()), this, SLOT(onSceneChanged()));
}

SceneDockWidget::~SceneDockWidget()
{
    delete ui;
}

void SceneDockWidget::onSceneChanged()
{
    rebuildSceneGraph();
    rebuildMeshList();
}

void SceneDockWidget::rebuildSceneGraph()
{
    SceneData* data = controller->getSceneData();

    QTreeWidget* sceneGraph = ui->treeWidgetSceneGraph;

    QTreeWidgetItem* top;
    while((top = sceneGraph->takeTopLevelItem(0)) != 0);

    QTreeWidgetItem* root = createNodeItem(data->rootNode);
    sceneGraph->addTopLevelItem(root);

    sceneGraph->expandAll();
}

void SceneDockWidget::rebuildMeshList()
{
    SceneData* data = controller->getSceneData();

    QListWidget* meshList = ui->listWidgetMeshes;
    meshList->clear();

    for(unsigned int i = 0; i < data->meshes.size(); ++i)
    {
        Mesh* mesh = data->meshes.at(i).get();

        meshList->addItem(QString("Mesh%1").arg(i));
    }
}

QTreeWidgetItem* SceneDockWidget::createNodeItem(const boost::shared_ptr<SceneNode>& node)
{
    QTreeWidgetItem* item = new QTreeWidgetItem((QTreeWidget*) 0, 1);

    item->setText(0, QString::fromStdString(node->name));

    for(unsigned int i = 0; i < node->children.size(); ++i)
    {
        item->addChild(createNodeItem(node->children.at(i)));
    }

    return item;
}
