#include "parUI/mjunctiondialog.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

MJunctionDialog::MJunctionDialog(std::shared_ptr<MJunction> junction, QString name, QWidget* parent)
    : QDialog(parent), _junction(junction) {
    setWindowIcon(QIcon(":/resources/image/icon.jpeg"));
    mName = name;
    setupUI();
    updateName();
    updateDialogFromMJuction();
}

void MJunctionDialog::setupUI() {
    junctionNameLabel = new QLabel("名称: ", this);
    junctionNameLineEdit = new QLineEdit(this);

    okButton = new QPushButton("确认");
    cancelButton = new QPushButton("取消");

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addWidget(junctionNameLabel);
    mainLayout->addWidget(junctionNameLineEdit);

    QHBoxLayout* buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);

    mainLayout->addLayout(buttonLayout);
    setLayout(mainLayout);

    connect(okButton, &QPushButton::clicked, this, &MJunctionDialog::acceptDialog);
    connect(cancelButton, &QPushButton::clicked, this, &MJunctionDialog::rejectDialog);

    setStyleSheet("QDialog { background-color: #f0f0f0; }"
        "QLabel { font-weight: bold; color: #333333; }"
        "QLineEdit { background-color: #ffffff; border: 1px solid #cccccc; padding: 5px; }"
        "QComboBox { background-color: #ffffff; border: 1px solid #cccccc; padding: 5px; }"
        "QPushButton { background-color: #4CAF50; color: white; border: none; padding: 10px; }"
        "QPushButton:hover { background-color: #45a049; }"
        "QPushButton:pressed { background-color: #367c39; }");
}

void MJunctionDialog::updateDialogFromMJuction() {
}

void MJunctionDialog::updateMJuctionFromDialog() {
    mName = junctionNameLineEdit->text();
}

QString MJunctionDialog::getName() {
    return mName;
}

void MJunctionDialog::acceptDialog() {
    updateMJuctionFromDialog();
    accept();
}

void MJunctionDialog::rejectDialog() {
    reject();
}

void MJunctionDialog::updateName() {
    if (!mName.isEmpty()) {
        junctionNameLineEdit->setText(mName);
    }
}
