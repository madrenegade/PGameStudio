/********************************************************************************
** Form generated from reading UI file 'singleviewwidget.ui'
**
** Created: 
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SINGLEVIEWWIDGET_H
#define UI_SINGLEVIEWWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SingleViewWidget
{
public:
    QHBoxLayout *horizontalLayout;

    void setupUi(QWidget *SingleViewWidget)
    {
        if (SingleViewWidget->objectName().isEmpty())
            SingleViewWidget->setObjectName(QString::fromUtf8("SingleViewWidget"));
        SingleViewWidget->resize(777, 515);
        horizontalLayout = new QHBoxLayout(SingleViewWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));

        retranslateUi(SingleViewWidget);

        QMetaObject::connectSlotsByName(SingleViewWidget);
    } // setupUi

    void retranslateUi(QWidget *SingleViewWidget)
    {
        SingleViewWidget->setWindowTitle(QApplication::translate("SingleViewWidget", "Form", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SingleViewWidget: public Ui_SingleViewWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SINGLEVIEWWIDGET_H
