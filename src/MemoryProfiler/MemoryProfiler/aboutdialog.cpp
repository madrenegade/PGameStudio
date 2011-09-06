#include "aboutdialog.h"
#include "ui_aboutdialog.h"
#include "memprof/memprof.h"

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);


    ui->memprofVersionLabel->setText(QString("build-%1").arg(memprof::getVersion()));
}

AboutDialog::~AboutDialog()
{
    delete ui;
}
