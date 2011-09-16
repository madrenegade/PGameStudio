#ifndef ASSETIMPORTWIZARD_H
#define ASSETIMPORTWIZARD_H

#include <QWizard>

namespace Ui {
    class AssetImportWizard;
}

class AssetImportWizard : public QWizard
{
    Q_OBJECT

public:
    explicit AssetImportWizard(QWidget *parent = 0);
    ~AssetImportWizard();

private:
    Ui::AssetImportWizard *ui;
};

#endif // ASSETIMPORTWIZARD_H
