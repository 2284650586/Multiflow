#ifndef MSOURCEDIALOG_H
#define MSOURCEDIALOG_H

#include <QDialog>
#include <QObject>

#include "entity/msource.h"

class QLabel;
class QLineEdit;
class QComboBox;

class MSourceDialog : public QDialog
{
    Q_OBJECT
public:
    explicit MSourceDialog(MSource* source, bool isNew, QString name, QWidget *parent = nullptr);
    ~MSourceDialog();


private slots:
    void acceptDialog();
    void rejectDialog();

private:
    MSource *mSource = nullptr;
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

#endif // MSOURCEDIALOG_H
