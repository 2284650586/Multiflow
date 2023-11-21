#pragma once

#include <QDialog>
#include <QObject>

#include "entity/MSink.hpp"

class QLabel;
class QLineEdit;
class QComboBox;

class MSinkDialog : public QDialog {
    Q_OBJECT

public:
    explicit MSinkDialog(MSink* sink, QString name, QWidget* parent = nullptr);

    ~MSinkDialog();

private slots:
    void acceptDialog();

    void rejectDialog();

private:
    MSink* _sink{};
    QString mName;

    QLabel* sinkNameLabel;
    QLabel* sinkPressureLabel;
    QLabel* sinkTemperatureLabel;
    QLabel* sinkFlowTypeLabel;
    QLabel* sinkFlowRateLabel;
    QLineEdit* sinkNameLineEdit;
    QLineEdit* sinkPressureLineEdit;
    QLineEdit* sinkTemperatureLineEdit;
    QComboBox* sinkFlowTypeComboBox;
    QLineEdit* sinkFlowRateLineEdit;
    QPushButton* okButton;
    QPushButton* cancelButton;

    void setupUI();

    void updateDialogFromMSink();

    void updateMSinkFromDialog();

    void updateName();

public:
    QString getName();
};
