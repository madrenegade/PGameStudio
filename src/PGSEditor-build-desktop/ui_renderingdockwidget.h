/********************************************************************************
** Form generated from reading UI file 'renderingdockwidget.ui'
**
** Created: 
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RENDERINGDOCKWIDGET_H
#define UI_RENDERINGDOCKWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDockWidget>
#include <QtGui/QFormLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QRadioButton>
#include <QtGui/QTabWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RenderingDockWidget
{
public:
    QWidget *dockWidgetContents;
    QHBoxLayout *horizontalLayout;
    QTabWidget *tabWidgetRendering;
    QWidget *tabRenderModes;
    QFormLayout *formLayout;
    QRadioButton *radioButtonWireframe;
    QRadioButton *radioButtonTextured;
    QRadioButton *radioButtonShaded;
    QWidget *tabDebugDrawing;
    QFormLayout *formLayout_2;

    void setupUi(QDockWidget *RenderingDockWidget)
    {
        if (RenderingDockWidget->objectName().isEmpty())
            RenderingDockWidget->setObjectName(QString::fromUtf8("RenderingDockWidget"));
        RenderingDockWidget->resize(724, 515);
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QString::fromUtf8("dockWidgetContents"));
        horizontalLayout = new QHBoxLayout(dockWidgetContents);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        tabWidgetRendering = new QTabWidget(dockWidgetContents);
        tabWidgetRendering->setObjectName(QString::fromUtf8("tabWidgetRendering"));
        tabRenderModes = new QWidget();
        tabRenderModes->setObjectName(QString::fromUtf8("tabRenderModes"));
        formLayout = new QFormLayout(tabRenderModes);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        radioButtonWireframe = new QRadioButton(tabRenderModes);
        radioButtonWireframe->setObjectName(QString::fromUtf8("radioButtonWireframe"));

        formLayout->setWidget(0, QFormLayout::LabelRole, radioButtonWireframe);

        radioButtonTextured = new QRadioButton(tabRenderModes);
        radioButtonTextured->setObjectName(QString::fromUtf8("radioButtonTextured"));

        formLayout->setWidget(1, QFormLayout::LabelRole, radioButtonTextured);

        radioButtonShaded = new QRadioButton(tabRenderModes);
        radioButtonShaded->setObjectName(QString::fromUtf8("radioButtonShaded"));

        formLayout->setWidget(2, QFormLayout::LabelRole, radioButtonShaded);

        tabWidgetRendering->addTab(tabRenderModes, QString());
        tabDebugDrawing = new QWidget();
        tabDebugDrawing->setObjectName(QString::fromUtf8("tabDebugDrawing"));
        formLayout_2 = new QFormLayout(tabDebugDrawing);
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        formLayout_2->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        tabWidgetRendering->addTab(tabDebugDrawing, QString());

        horizontalLayout->addWidget(tabWidgetRendering);

        RenderingDockWidget->setWidget(dockWidgetContents);

        retranslateUi(RenderingDockWidget);

        tabWidgetRendering->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(RenderingDockWidget);
    } // setupUi

    void retranslateUi(QDockWidget *RenderingDockWidget)
    {
        RenderingDockWidget->setWindowTitle(QApplication::translate("RenderingDockWidget", "Rendering", 0, QApplication::UnicodeUTF8));
        radioButtonWireframe->setText(QApplication::translate("RenderingDockWidget", "Wireframe", 0, QApplication::UnicodeUTF8));
        radioButtonTextured->setText(QApplication::translate("RenderingDockWidget", "Textured", 0, QApplication::UnicodeUTF8));
        radioButtonShaded->setText(QApplication::translate("RenderingDockWidget", "Shaded", 0, QApplication::UnicodeUTF8));
        tabWidgetRendering->setTabText(tabWidgetRendering->indexOf(tabRenderModes), QApplication::translate("RenderingDockWidget", "Render Modes", 0, QApplication::UnicodeUTF8));
        tabWidgetRendering->setTabText(tabWidgetRendering->indexOf(tabDebugDrawing), QApplication::translate("RenderingDockWidget", "Debug Drawing", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class RenderingDockWidget: public Ui_RenderingDockWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RENDERINGDOCKWIDGET_H
