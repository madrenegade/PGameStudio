#ifndef NEWSCENEWIZARD_H
#define NEWSCENEWIZARD_H

#include <QWizard>

namespace Ui {
    class Wizard;
}

class NewSceneWizard : public QWizard
{
    Q_OBJECT

public:
    explicit NewSceneWizard(QWidget *parent = 0);
    ~NewSceneWizard();

    QStringList selectedSystems() const;

private:
    Ui::Wizard *ui;
};

#endif // NEWSCENEWIZARD_H
