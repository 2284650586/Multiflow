#include "MSourceDialog.hpp"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QSharedPointer>

MSourceDialog::MSourceDialog(MSource* source, QString name, QWidget* parent)
    : QDialog(parent), _source(source) {
    setWindowIcon(QIcon(":/resources/image/icon.jpeg"));
    mName = name;
    setupUI();
    updateName();
    updateDialogFromMSource();
}

MSourceDialog::~MSourceDialog() {
}

void MSourceDialog::setupUI() {
    // Create UI components
    sourceNameLabel = new QLabel("名称: ", this);
    sourcePressureLabel = new QLabel("源压力(Mpa a):", this);
    sourceTemperatureLabel = new QLabel("源温度(DegC):", this);
    sourceFlowTypeLabel = new QLabel("源流动类型:", this);
    sourceFlowRateLabel = new QLabel("源流动流量(sm^3):", this);
    sourceNameLineEdit = new QLineEdit(this);
    sourcePressureLineEdit = new QLineEdit(this);
    sourceTemperatureLineEdit = new QLineEdit(this);
    sourceFlowTypeComboBox = new QComboBox(this);
    sourceFlowRateLineEdit = new QLineEdit(this);

    QDoubleValidator* doubleValidator = new QDoubleValidator(this);
    doubleValidator->setNotation(QDoubleValidator::StandardNotation);
    doubleValidator->setDecimals(15);

    sourcePressureLineEdit->setValidator(doubleValidator);
    sourceTemperatureLineEdit->setValidator(doubleValidator);
    sourceFlowRateLineEdit->setValidator(doubleValidator);

    okButton = new QPushButton("确认");
    cancelButton = new QPushButton("取消");

    sourceFlowTypeComboBox->addItem("液体流量");
    sourceFlowTypeComboBox->addItem("气体流量");
    sourceFlowTypeComboBox->addItem("质量流量");

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addWidget(sourceNameLabel);
    mainLayout->addWidget(sourceNameLineEdit);
    mainLayout->addWidget(sourcePressureLabel);
    mainLayout->addWidget(sourcePressureLineEdit);
    mainLayout->addWidget(sourceTemperatureLabel);
    mainLayout->addWidget(sourceTemperatureLineEdit);
    mainLayout->addWidget(sourceFlowTypeLabel);
    mainLayout->addWidget(sourceFlowTypeComboBox);
    mainLayout->addWidget(sourceFlowRateLabel);
    mainLayout->addWidget(sourceFlowRateLineEdit);

    QHBoxLayout* buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);

    mainLayout->addLayout(buttonLayout);
    setLayout(mainLayout);

    connect(okButton, &QPushButton::clicked, this, &MSourceDialog::acceptDialog);
    connect(cancelButton, &QPushButton::clicked, this, &MSourceDialog::rejectDialog);

    setStyleSheet("QDialog { background-color: #f0f0f0; }"
        "QLabel { font-weight: bold; color: #333333; }"
        "QLineEdit { background-color: #ffffff; border: 1px solid #cccccc; padding: 5px; }"
        "QComboBox { background-color: #ffffff; border: 1px solid #cccccc; padding: 5px; }"
        "QPushButton { background-color: #4CAF50; color: white; border: none; padding: 10px; }"
        "QPushButton:hover { background-color: #45a049; }"
        "QPushButton:pressed { background-color: #367c39; }");
}

void MSourceDialog::updateDialogFromMSource() {
    if (_source) {
        sourcePressureLineEdit->setText(QString::number(_source->sourcePressure));
        sourceTemperatureLineEdit->setText(QString::number(_source->sourceTemperature));
        sourceFlowRateLineEdit->setText(QString::number(_source->sourceFlowRate));

        switch (_source->sourceFlowType) {
            case MSource::Liquid:
                sourceFlowTypeComboBox->setCurrentIndex(0);
                break;
            case MSource::Gas:
                sourceFlowTypeComboBox->setCurrentIndex(1);
                break;
            case MSource::Mass:
                sourceFlowTypeComboBox->setCurrentIndex(2);
                break;
        }
    }
}

void MSourceDialog::updateMSourceFromDialog() {
    if (_source) {
        mName = sourceNameLineEdit->text();
        _source->sourcePressure = sourcePressureLineEdit->text().toDouble();
        _source->sourceTemperature = sourceTemperatureLineEdit->text().toDouble();
        _source->sourceFlowRate = sourceFlowRateLineEdit->text().toDouble();

        switch (sourceFlowTypeComboBox->currentIndex()) {
            case 0:
                _source->sourceFlowType = MSource::Liquid;
                break;
            case 1:
                _source->sourceFlowType = MSource::Gas;
                break;
            case 2:
                _source->sourceFlowType = MSource::Mass;
                break;
        }
    }
}

void MSourceDialog::updateName() {
    if (!mName.isEmpty()) {
        sourceNameLineEdit->setText(mName);
    }
}

QString MSourceDialog::getName() {
    return mName;
}

void MSourceDialog::acceptDialog() {
    updateMSourceFromDialog();
    accept();
}

void MSourceDialog::rejectDialog() {
    reject();
}
