#ifndef NEWSCENEWIZARD_H
#define NEWSCENEWIZARD_H

#include <QWizard>
#include <QCheckBox>

namespace Ui {
    class Wizard;
}

class Controller;

class NewSceneWizard : public QWizard
{
    Q_OBJECT

public:
    explicit NewSceneWizard(Controller* controller, QWidget *parent = 0);
    ~NewSceneWizard();

    QStringList selectedSystems() const;

private:
    Ui::Wizard *ui;

    Controller* controller;

    QList<const QCheckBox*> systemCheckboxes;
};

#endif // NEWSCENEWIZARD_H
