#ifndef MJUNCTIONDIALOG_H
#define MJUNCTIONDIALOG_H

#include <QDialog>
#include <QObject>

#include "entity/mjunction.h"

class QLineEdit;
class QLabel;
class MJunctionDialog : public QDialog
{
    Q_OBJECT
public:
    MJunctionDialog(MJunction* junction, QString name, QWidget *parent = nullptr);

    QString mName;
    MJunction* _junction;

    QString getName();

private slots:
    void acceptDialog();
    void rejectDialog();

private:
    void setupUI();
    void updateName();
    void updateDialogFromMJuction();
    void updateMJuctionFromDialog();

    QLabel* junctionNameLabel;
    QLineEdit* junctionNameLineEdit;

    QPushButton* okButton;
    QPushButton* cancelButton;
};

#endif // MJUNCTIONDIALOG_H
