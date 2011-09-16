/********************************************************************************
** Form generated from reading UI file 'multiviewwidget.ui'
**
** Created: 
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MULTIVIEWWIDGET_H
#define UI_MULTIVIEWWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MultiViewWidget
{
public:
    QHBoxLayout *horizontalLayout;
    QGridLayout *gridLayout;

    void setupUi(QWidget *MultiViewWidget)
    {
        if (MultiViewWidget->objectName().isEmpty())
            MultiViewWidget->setObjectName(QString::fromUtf8("MultiViewWidget"));
        MultiViewWidget->resize(400, 300);
        horizontalLayout = new QHBoxLayout(MultiViewWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));

        horizontalLayout->addLayout(gridLayout);


        retranslateUi(MultiViewWidget);

        QMetaObject::connectSlotsByName(MultiViewWidget);
    } // setupUi

    void retranslateUi(QWidget *MultiViewWidget)
    {
        MultiViewWidget->setWindowTitle(QApplication::translate("MultiViewWidget", "Form", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MultiViewWidget: public Ui_MultiViewWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MULTIVIEWWIDGET_H
