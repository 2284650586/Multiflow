#pragma once

#include <QDialog>
#include <QObject>

#include "entity/MSource.hpp"

class QLabel;
class QLineEdit;
class QComboBox;

class MSourceDialog : public QDialog {
    Q_OBJECT

public:
    explicit MSourceDialog(MSource* source, QString name, QWidget* parent = nullptr);

    ~MSourceDialog();

private slots:
    void acceptDialog();

    void rejectDialog();

private:
    MSource* _source{};
    QString mName;

    QLabel* sourceNameLabel;
    QLabel* sourcePressureLabel;
    QLabel* sourceTemperatureLabel;
    QLabel* sourceFlowTypeLabel;
    QLabel* sourceFlowRateLabel;
    QLineEdit* sourceNameLineEdit;
    QLineEdit* sourcePressureLineEdit;
    QLineEdit* sourceTemperatureLineEdit;
    QComboBox* sourceFlowTypeComboBox;
    QLineEdit* sourceFlowRateLineEdit;
    QPushButton* okButton;
    QPushButton* cancelButton;

    void setupUI();

    void updateDialogFromMSource();

    void updateMSourceFromDialog();

    void updateName();

public:
    QString getName();
};
