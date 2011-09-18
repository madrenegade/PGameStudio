/********************************************************************************
** Form generated from reading UI file 'assetimportwizard.ui'
**
** Created: 
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ASSETIMPORTWIZARD_H
#define UI_ASSETIMPORTWIZARD_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFormLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWizard>
#include <QtGui/QWizardPage>

QT_BEGIN_NAMESPACE

class Ui_AssetImportWizard
{
public:
    QWizardPage *wizardPageGeneral;
    QFormLayout *formLayout;
    QLabel *label;
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineEditFilename;
    QPushButton *pushButtonChooseFile;
    QWizardPage *wizardPageOptimizations;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QWizardPage *wizardPageConfirm;

    void setupUi(QWizard *AssetImportWizard)
    {
        if (AssetImportWizard->objectName().isEmpty())
            AssetImportWizard->setObjectName(QString::fromUtf8("AssetImportWizard"));
        AssetImportWizard->resize(572, 400);
        wizardPageGeneral = new QWizardPage();
        wizardPageGeneral->setObjectName(QString::fromUtf8("wizardPageGeneral"));
        formLayout = new QFormLayout(wizardPageGeneral);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        label = new QLabel(wizardPageGeneral);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        lineEditFilename = new QLineEdit(wizardPageGeneral);
        lineEditFilename->setObjectName(QString::fromUtf8("lineEditFilename"));

        horizontalLayout->addWidget(lineEditFilename);

        pushButtonChooseFile = new QPushButton(wizardPageGeneral);
        pushButtonChooseFile->setObjectName(QString::fromUtf8("pushButtonChooseFile"));

        horizontalLayout->addWidget(pushButtonChooseFile);


        formLayout->setLayout(1, QFormLayout::FieldRole, horizontalLayout);

        AssetImportWizard->addPage(wizardPageGeneral);
        wizardPageOptimizations = new QWizardPage();
        wizardPageOptimizations->setObjectName(QString::fromUtf8("wizardPageOptimizations"));
        verticalLayout_2 = new QVBoxLayout(wizardPageOptimizations);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));

        verticalLayout_2->addLayout(verticalLayout);

        AssetImportWizard->addPage(wizardPageOptimizations);
        wizardPageConfirm = new QWizardPage();
        wizardPageConfirm->setObjectName(QString::fromUtf8("wizardPageConfirm"));
        AssetImportWizard->addPage(wizardPageConfirm);

        retranslateUi(AssetImportWizard);
        QObject::connect(pushButtonChooseFile, SIGNAL(clicked()), AssetImportWizard, SLOT(onChooseFile()));

        QMetaObject::connectSlotsByName(AssetImportWizard);
    } // setupUi

    void retranslateUi(QWizard *AssetImportWizard)
    {
        AssetImportWizard->setWindowTitle(QApplication::translate("AssetImportWizard", "Wizard", 0, QApplication::UnicodeUTF8));
        wizardPageGeneral->setTitle(QApplication::translate("AssetImportWizard", "Import Asset", 0, QApplication::UnicodeUTF8));
        wizardPageGeneral->setSubTitle(QApplication::translate("AssetImportWizard", "General", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("AssetImportWizard", "File:", 0, QApplication::UnicodeUTF8));
        pushButtonChooseFile->setText(QApplication::translate("AssetImportWizard", "...", 0, QApplication::UnicodeUTF8));
        wizardPageOptimizations->setTitle(QApplication::translate("AssetImportWizard", "Import Asset", 0, QApplication::UnicodeUTF8));
        wizardPageOptimizations->setSubTitle(QApplication::translate("AssetImportWizard", "Optimizations", 0, QApplication::UnicodeUTF8));
        wizardPageConfirm->setTitle(QApplication::translate("AssetImportWizard", "Import Asset", 0, QApplication::UnicodeUTF8));
        wizardPageConfirm->setSubTitle(QApplication::translate("AssetImportWizard", "Overview", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class AssetImportWizard: public Ui_AssetImportWizard {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ASSETIMPORTWIZARD_H
