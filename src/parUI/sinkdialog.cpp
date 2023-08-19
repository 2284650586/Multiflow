#include "sinkdialog.h"
#include "ui_sinkdialog.h"

sinkDialog::sinkDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::sinkDialog)
{
    ui->setupUi(this);
}

sinkDialog::~sinkDialog()
{
    delete ui;
}

void sinkDialog::on_btnOK_clicked()
{
    close();
}


void sinkDialog::on_btnCancel_clicked()
{
    close();
}

