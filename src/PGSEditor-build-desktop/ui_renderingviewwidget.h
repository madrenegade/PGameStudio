/********************************************************************************
** Form generated from reading UI file 'renderingviewwidget.ui'
**
** Created: 
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RENDERINGVIEWWIDGET_H
#define UI_RENDERINGVIEWWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGraphicsView>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RenderingViewWidget
{
public:
    QHBoxLayout *horizontalLayout;
    QGraphicsView *graphicsView;

    void setupUi(QWidget *RenderingViewWidget)
    {
        if (RenderingViewWidget->objectName().isEmpty())
            RenderingViewWidget->setObjectName(QString::fromUtf8("RenderingViewWidget"));
        RenderingViewWidget->resize(400, 300);
        horizontalLayout = new QHBoxLayout(RenderingViewWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        graphicsView = new QGraphicsView(RenderingViewWidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));

        horizontalLayout->addWidget(graphicsView);


        retranslateUi(RenderingViewWidget);

        QMetaObject::connectSlotsByName(RenderingViewWidget);
    } // setupUi

    void retranslateUi(QWidget *RenderingViewWidget)
    {
        RenderingViewWidget->setWindowTitle(QApplication::translate("RenderingViewWidget", "Form", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class RenderingViewWidget: public Ui_RenderingViewWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RENDERINGVIEWWIDGET_H
