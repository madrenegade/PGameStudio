#include "assetimportwizard.h"
#include "ui_assetimportwizard.h"
#include "controller.h"

#include <QFileDialog>

AssetImportWizard::AssetImportWizard(Controller* controller, QWidget *parent) :
    QWizard(parent),
    ui(new Ui::AssetImportWizard), controller(controller)
{
    ui->setupUi(this);

    QStringList postProcessingSteps(controller->getAssetImportPostProcessingSteps());

    auto page = ui->wizardPageOptimizations;

    for(auto i = postProcessingSteps.begin(); i != postProcessingSteps.end(); ++i)
    {
        auto checkBox = new QCheckBox(*i, page);
        page->layout()->addWidget(checkBox);
    }
}

AssetImportWizard::~AssetImportWizard()
{
    delete ui;
}

QString AssetImportWizard::getFilename() const
{
    return ui->lineEditFilename->text();
}

void AssetImportWizard::onChooseFile()
{
    QString filename = QFileDialog::getOpenFileName(this);

    ui->lineEditFilename->setText(filename);
}
