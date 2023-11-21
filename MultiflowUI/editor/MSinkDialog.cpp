#include "MSinkDialog.hpp"
#include <QHBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>

MSinkDialog::MSinkDialog(MSink* sink, QString name, QWidget* parent)
    : QDialog(parent), _sink(sink) {
    setWindowIcon(QIcon(":/resources/image/icon.jpeg"));
    mName = name;
    setupUI();
    updateName();
    updateDialogFromMSink();
}

MSinkDialog::~MSinkDialog() {
}

void MSinkDialog::setupUI() {
    // Create UI components
    sinkNameLabel = new QLabel("名称: ", this);
    sinkPressureLabel = new QLabel("源压力(Mpa a):", this);
    sinkTemperatureLabel = new QLabel("源温度(DegC):", this);
    sinkFlowTypeLabel = new QLabel("源流动类型:", this);
    sinkFlowRateLabel = new QLabel("源流动流量(sm^3):", this);
    sinkNameLineEdit = new QLineEdit(this);
    sinkPressureLineEdit = new QLineEdit(this);
    sinkTemperatureLineEdit = new QLineEdit(this);
    sinkFlowTypeComboBox = new QComboBox(this);
    sinkFlowRateLineEdit = new QLineEdit(this);

    QDoubleValidator* doubleValidator = new QDoubleValidator(this);
    doubleValidator->setNotation(QDoubleValidator::StandardNotation);
    doubleValidator->setDecimals(15);

    sinkPressureLineEdit->setValidator(doubleValidator);
    sinkTemperatureLineEdit->setValidator(doubleValidator);
    sinkFlowRateLineEdit->setValidator(doubleValidator);

    okButton = new QPushButton("确认");
    cancelButton = new QPushButton("取消");

    sinkFlowTypeComboBox->addItem("液体流量");
    sinkFlowTypeComboBox->addItem("气体流量");
    sinkFlowTypeComboBox->addItem("质量流量");

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addWidget(sinkNameLabel);
    mainLayout->addWidget(sinkNameLineEdit);
    mainLayout->addWidget(sinkPressureLabel);
    mainLayout->addWidget(sinkPressureLineEdit);
    mainLayout->addWidget(sinkTemperatureLabel);
    mainLayout->addWidget(sinkTemperatureLineEdit);
    mainLayout->addWidget(sinkFlowTypeLabel);
    mainLayout->addWidget(sinkFlowTypeComboBox);
    mainLayout->addWidget(sinkFlowRateLabel);
    mainLayout->addWidget(sinkFlowRateLineEdit);

    QHBoxLayout* buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);

    mainLayout->addLayout(buttonLayout);
    setLayout(mainLayout);

    connect(okButton, &QPushButton::clicked, this, &MSinkDialog::acceptDialog);
    connect(cancelButton, &QPushButton::clicked, this, &MSinkDialog::rejectDialog);

    setStyleSheet("QDialog { background-color: #f0f0f0; }"
        "QLabel { font-weight: bold; color: #333333; }"
        "QLineEdit { background-color: #ffffff; border: 1px solid #cccccc; padding: 5px; }"
        "QComboBox { background-color: #ffffff; border: 1px solid #cccccc; padding: 5px; }"
        "QPushButton { background-color: #4CAF50; color: white; border: none; padding: 10px; }"
        "QPushButton:hover { background-color: #45a049; }"
        "QPushButton:pressed { background-color: #367c39; }");
}

void MSinkDialog::updateDialogFromMSink() {
    if (_sink) {
        sinkPressureLineEdit->setText(QString::number(_sink->sinkPressure));
        sinkTemperatureLineEdit->setText(QString::number(_sink->sinkTemperature));
        sinkFlowRateLineEdit->setText(QString::number(_sink->sinkFlowRate));

        switch (_sink->sinkFlowType) {
            case MSink::Liquid:
                sinkFlowTypeComboBox->setCurrentIndex(0);
                break;
            case MSink::Gas:
                sinkFlowTypeComboBox->setCurrentIndex(1);
                break;
            case MSink::Mass:
                sinkFlowTypeComboBox->setCurrentIndex(2);
                break;
        }
    }
}

void MSinkDialog::updateMSinkFromDialog() {
    if (_sink) {
        mName = sinkNameLineEdit->text();
        _sink->sinkPressure = sinkPressureLineEdit->text().toDouble();
        _sink->sinkTemperature = sinkTemperatureLineEdit->text().toDouble();
        _sink->sinkFlowRate = sinkFlowRateLineEdit->text().toDouble();

        switch (sinkFlowTypeComboBox->currentIndex()) {
            case 0:
                _sink->sinkFlowType = MSink::Liquid;
                break;
            case 1:
                _sink->sinkFlowType = MSink::Gas;
                break;
            case 2:
                _sink->sinkFlowType = MSink::Mass;
                break;
        }
    }
}

void MSinkDialog::updateName() {
    if (!mName.isEmpty()) {
        sinkNameLineEdit->setText(mName);
    }
}

QString MSinkDialog::getName() {
    return mName;
}

void MSinkDialog::acceptDialog() {
    updateMSinkFromDialog();
    accept();
}

void MSinkDialog::rejectDialog() {
    reject();
}
