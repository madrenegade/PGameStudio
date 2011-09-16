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
#include <QtGui/QHeaderView>
#include <QtGui/QWizard>
#include <QtGui/QWizardPage>

QT_BEGIN_NAMESPACE

class Ui_AssetImportWizard
{
public:
    QWizardPage *wizardPageGeneral;
    QWizardPage *wizardPageOptimizations;
    QWizardPage *wizardPageConfirm;

    void setupUi(QWizard *AssetImportWizard)
    {
        if (AssetImportWizard->objectName().isEmpty())
            AssetImportWizard->setObjectName(QString::fromUtf8("AssetImportWizard"));
        AssetImportWizard->resize(797, 470);
        wizardPageGeneral = new QWizardPage();
        wizardPageGeneral->setObjectName(QString::fromUtf8("wizardPageGeneral"));
        AssetImportWizard->addPage(wizardPageGeneral);
        wizardPageOptimizations = new QWizardPage();
        wizardPageOptimizations->setObjectName(QString::fromUtf8("wizardPageOptimizations"));
        AssetImportWizard->addPage(wizardPageOptimizations);
        wizardPageConfirm = new QWizardPage();
        wizardPageConfirm->setObjectName(QString::fromUtf8("wizardPageConfirm"));
        AssetImportWizard->addPage(wizardPageConfirm);

        retranslateUi(AssetImportWizard);

        QMetaObject::connectSlotsByName(AssetImportWizard);
    } // setupUi

    void retranslateUi(QWizard *AssetImportWizard)
    {
        AssetImportWizard->setWindowTitle(QApplication::translate("AssetImportWizard", "Wizard", 0, QApplication::UnicodeUTF8));
        wizardPageGeneral->setTitle(QApplication::translate("AssetImportWizard", "Import Asset", 0, QApplication::UnicodeUTF8));
        wizardPageGeneral->setSubTitle(QApplication::translate("AssetImportWizard", "General", 0, QApplication::UnicodeUTF8));
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
