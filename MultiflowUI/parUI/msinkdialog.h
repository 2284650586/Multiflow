#ifndef MSINKDIALOG_H
#define MSINKDIALOG_H

#include <QDialog>
#include <QObject>

#include "entity/msink.h"

class QLabel;
class QLineEdit;
class QComboBox;

class MSinkDialog : public QDialog
{
    Q_OBJECT
public:
    explicit MSinkDialog(MSink* sink, bool isNew, QString name, QWidget *parent = nullptr);
    ~MSinkDialog();


private slots:
    void acceptDialog();
    void rejectDialog();

private:
    MSink *mSink = nullptr;
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

#endif // MSINKDIALOG_H
