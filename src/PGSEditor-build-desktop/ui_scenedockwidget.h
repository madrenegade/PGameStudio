/********************************************************************************
** Form generated from reading UI file 'scenedockwidget.ui'
**
** Created: 
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SCENEDOCKWIDGET_H
#define UI_SCENEDOCKWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDockWidget>
#include <QtGui/QGraphicsView>
#include <QtGui/QHeaderView>
#include <QtGui/QListWidget>
#include <QtGui/QTabWidget>
#include <QtGui/QTreeWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SceneDockWidget
{
public:
    QWidget *dockWidgetContents;
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *tab;
    QVBoxLayout *verticalLayout_2;
    QTreeWidget *treeWidgetSceneGraph;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout_3;
    QListWidget *listWidgetMeshes;
    QWidget *tab_3;
    QVBoxLayout *verticalLayout_4;
    QListWidget *listWidgetMaterials;
    QGraphicsView *materialPreview;
    QWidget *tab_4;
    QVBoxLayout *verticalLayout_5;
    QListWidget *listWidgetTextures;
    QGraphicsView *texturePreview;

    void setupUi(QDockWidget *SceneDockWidget)
    {
        if (SceneDockWidget->objectName().isEmpty())
            SceneDockWidget->setObjectName(QString::fromUtf8("SceneDockWidget"));
        SceneDockWidget->resize(439, 474);
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QString::fromUtf8("dockWidgetContents"));
        verticalLayout = new QVBoxLayout(dockWidgetContents);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        tabWidget = new QTabWidget(dockWidgetContents);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        verticalLayout_2 = new QVBoxLayout(tab);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        treeWidgetSceneGraph = new QTreeWidget(tab);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        treeWidgetSceneGraph->setHeaderItem(__qtreewidgetitem);
        treeWidgetSceneGraph->setObjectName(QString::fromUtf8("treeWidgetSceneGraph"));
        treeWidgetSceneGraph->header()->setVisible(false);

        verticalLayout_2->addWidget(treeWidgetSceneGraph);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        verticalLayout_3 = new QVBoxLayout(tab_2);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        listWidgetMeshes = new QListWidget(tab_2);
        listWidgetMeshes->setObjectName(QString::fromUtf8("listWidgetMeshes"));

        verticalLayout_3->addWidget(listWidgetMeshes);

        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        verticalLayout_4 = new QVBoxLayout(tab_3);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        listWidgetMaterials = new QListWidget(tab_3);
        listWidgetMaterials->setObjectName(QString::fromUtf8("listWidgetMaterials"));

        verticalLayout_4->addWidget(listWidgetMaterials);

        materialPreview = new QGraphicsView(tab_3);
        materialPreview->setObjectName(QString::fromUtf8("materialPreview"));
        materialPreview->setMinimumSize(QSize(0, 135));
        materialPreview->setMaximumSize(QSize(16777215, 135));

        verticalLayout_4->addWidget(materialPreview);

        tabWidget->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QString::fromUtf8("tab_4"));
        verticalLayout_5 = new QVBoxLayout(tab_4);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        listWidgetTextures = new QListWidget(tab_4);
        listWidgetTextures->setObjectName(QString::fromUtf8("listWidgetTextures"));

        verticalLayout_5->addWidget(listWidgetTextures);

        texturePreview = new QGraphicsView(tab_4);
        texturePreview->setObjectName(QString::fromUtf8("texturePreview"));
        texturePreview->setMinimumSize(QSize(0, 128));
        texturePreview->setMaximumSize(QSize(16777215, 128));

        verticalLayout_5->addWidget(texturePreview);

        tabWidget->addTab(tab_4, QString());

        verticalLayout->addWidget(tabWidget);

        SceneDockWidget->setWidget(dockWidgetContents);

        retranslateUi(SceneDockWidget);
        QObject::connect(listWidgetMaterials, SIGNAL(itemClicked(QListWidgetItem*)), SceneDockWidget, SLOT(onMaterialSelected(QListWidgetItem*)));

        tabWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(SceneDockWidget);
    } // setupUi

    void retranslateUi(QDockWidget *SceneDockWidget)
    {
        SceneDockWidget->setWindowTitle(QApplication::translate("SceneDockWidget", "Scene", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("SceneDockWidget", "Scene", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("SceneDockWidget", "Meshes", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("SceneDockWidget", "Materials", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QApplication::translate("SceneDockWidget", "Textures", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SceneDockWidget: public Ui_SceneDockWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCENEDOCKWIDGET_H
