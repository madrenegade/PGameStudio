#include "assetimportwizard.h"
#include "ui_assetimportwizard.h"

AssetImportWizard::AssetImportWizard(QWidget *parent) :
    QWizard(parent),
    ui(new Ui::AssetImportWizard)
{
    ui->setupUi(this);
}

AssetImportWizard::~AssetImportWizard()
{
    delete ui;
}
