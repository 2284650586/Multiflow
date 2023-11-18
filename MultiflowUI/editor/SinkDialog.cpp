#include "SinkDialog.hpp"
#include "ui_sinkdialog.h"

SinkDialog::SinkDialog(QWidget* parent)
    : QDialog(parent),
      ui(new Ui::sinkDialog) {
    ui->setupUi(this);
}

SinkDialog::~SinkDialog() {
    delete ui;
}

void SinkDialog::on_btnOK_clicked() {
    close();
}


void SinkDialog::on_btnCancel_clicked() {
    close();
}
