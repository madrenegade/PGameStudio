#ifndef ASSETIMPORTWIZARD_H
#define ASSETIMPORTWIZARD_H

#include <QWizard>

namespace Ui {
    class AssetImportWizard;
}

class Controller;

class AssetImportWizard : public QWizard
{
    Q_OBJECT

public:
    explicit AssetImportWizard(Controller* controller, QWidget *parent = 0);
    ~AssetImportWizard();

    QString getFilename() const;

public slots:
    void onChooseFile();

private:
    Ui::AssetImportWizard *ui;

    Controller* controller;
};

#endif // ASSETIMPORTWIZARD_H
