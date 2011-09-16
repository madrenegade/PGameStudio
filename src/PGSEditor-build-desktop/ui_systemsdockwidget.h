/********************************************************************************
** Form generated from reading UI file 'systemsdockwidget.ui'
**
** Created: 
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SYSTEMSDOCKWIDGET_H
#define UI_SYSTEMSDOCKWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDockWidget>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QTabWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SystemsDockWidget
{
public:
    QWidget *dockWidgetContents;
    QHBoxLayout *horizontalLayout;
    QTabWidget *tabWidget;

    void setupUi(QDockWidget *SystemsDockWidget)
    {
        if (SystemsDockWidget->objectName().isEmpty())
            SystemsDockWidget->setObjectName(QString::fromUtf8("SystemsDockWidget"));
        SystemsDockWidget->resize(747, 568);
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QString::fromUtf8("dockWidgetContents"));
        horizontalLayout = new QHBoxLayout(dockWidgetContents);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        tabWidget = new QTabWidget(dockWidgetContents);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));

        horizontalLayout->addWidget(tabWidget);

        SystemsDockWidget->setWidget(dockWidgetContents);

        retranslateUi(SystemsDockWidget);

        tabWidget->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(SystemsDockWidget);
    } // setupUi

    void retranslateUi(QDockWidget *SystemsDockWidget)
    {
        SystemsDockWidget->setWindowTitle(QApplication::translate("SystemsDockWidget", "Systems", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SystemsDockWidget: public Ui_SystemsDockWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SYSTEMSDOCKWIDGET_H
