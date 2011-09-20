/********************************************************************************
** Form generated from reading UI file 'newscenewizard.ui'
**
** Created: 
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWSCENEWIZARD_H
#define UI_NEWSCENEWIZARD_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFormLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWizard>
#include <QtGui/QWizardPage>

QT_BEGIN_NAMESPACE

class Ui_Wizard
{
public:
    QWizardPage *wizardPageGeneral;
    QFormLayout *formLayout_2;
    QLabel *label;
    QLineEdit *lineEditSceneName;
    QWizardPage *wizardPageSystems;
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;

    void setupUi(QWizard *Wizard)
    {
        if (Wizard->objectName().isEmpty())
            Wizard->setObjectName(QString::fromUtf8("Wizard"));
        Wizard->resize(690, 422);
        wizardPageGeneral = new QWizardPage();
        wizardPageGeneral->setObjectName(QString::fromUtf8("wizardPageGeneral"));
        formLayout_2 = new QFormLayout(wizardPageGeneral);
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        label = new QLabel(wizardPageGeneral);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label);

        lineEditSceneName = new QLineEdit(wizardPageGeneral);
        lineEditSceneName->setObjectName(QString::fromUtf8("lineEditSceneName"));

        formLayout_2->setWidget(0, QFormLayout::FieldRole, lineEditSceneName);

        Wizard->addPage(wizardPageGeneral);
        wizardPageSystems = new QWizardPage();
        wizardPageSystems->setObjectName(QString::fromUtf8("wizardPageSystems"));
        verticalLayout = new QVBoxLayout(wizardPageSystems);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));

        verticalLayout->addLayout(formLayout);

        Wizard->addPage(wizardPageSystems);

        retranslateUi(Wizard);

        QMetaObject::connectSlotsByName(Wizard);
    } // setupUi

    void retranslateUi(QWizard *Wizard)
    {
        Wizard->setWindowTitle(QApplication::translate("Wizard", "Wizard", 0, QApplication::UnicodeUTF8));
        wizardPageGeneral->setTitle(QApplication::translate("Wizard", "Create New Scene", 0, QApplication::UnicodeUTF8));
        wizardPageGeneral->setSubTitle(QApplication::translate("Wizard", "General", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Wizard", "Name:", 0, QApplication::UnicodeUTF8));
        wizardPageSystems->setTitle(QApplication::translate("Wizard", "Create New Scene", 0, QApplication::UnicodeUTF8));
        wizardPageSystems->setSubTitle(QApplication::translate("Wizard", "Needed Systems", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Wizard: public Ui_Wizard {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWSCENEWIZARD_H
