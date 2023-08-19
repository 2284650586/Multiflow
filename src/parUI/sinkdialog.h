#ifndef SINKDIALOG_H
#define SINKDIALOG_H

#include <QDialog>

namespace Ui {
class sinkDialog;
}

class sinkDialog : public QDialog
{
    Q_OBJECT

public:
    sinkDialog(QWidget *parent = nullptr);
    ~sinkDialog();

private slots:
    void on_btnOK_clicked();

    void on_btnCancel_clicked();

private:
    Ui::sinkDialog *ui;
};

#endif // SINKDIALOG_H
