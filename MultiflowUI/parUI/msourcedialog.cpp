#include "msourcedialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QSharedPointer>

MSourceDialog::MSourceDialog(MSource* source, bool isNew, QString name, QWidget *parent)
    : QDialog(parent)
{
    setWindowIcon(QIcon(":/resources/image/icon.jpeg"));
    mSource = source;
    mName = name;
    setupUI();
    updateName();
    if (!isNew) {
        updateDialogFromMSource();
    }
}

MSourceDialog::~MSourceDialog()
{

}

void MSourceDialog::setupUI()
{
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

void MSourceDialog::updateDialogFromMSource()
{
    if (mSource)
    {
        sourcePressureLineEdit->setText(QString::number(mSource->getSourcePressure()));
        sourceTemperatureLineEdit->setText(QString::number(mSource->getSourceTemperature()));
        sourceFlowRateLineEdit->setText(QString::number(mSource->getSourceFlowRate()));

        switch (mSource->getSourceFlowType())
        {
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

void MSourceDialog::updateMSourceFromDialog()
{
    if (mSource)
    {
        mName = sourceNameLineEdit->text();
        mSource->setSourcePressure(sourcePressureLineEdit->text().toDouble());
        mSource->setSourceTemperature(sourceTemperatureLineEdit->text().toDouble());
        mSource->setSourceFlowRate(sourceFlowRateLineEdit->text().toDouble());

        switch (sourceFlowTypeComboBox->currentIndex())
        {
        case 0:
            mSource->setSourceFlowType(MSource::Liquid);
            break;
        case 1:
            mSource->setSourceFlowType(MSource::Gas);
            break;
        case 2:
            mSource->setSourceFlowType(MSource::Mass);
            break;
        }
    }
}

void MSourceDialog::updateName()
{
    if (!mName.isEmpty()) {
        sourceNameLineEdit->setText(mName);
    }
}

QString MSourceDialog::getName()
{
    return mName;
}

void MSourceDialog::acceptDialog()
{
    updateMSourceFromDialog();
    accept();
}

void MSourceDialog::rejectDialog()
{
    reject();
}
