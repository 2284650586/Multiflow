#pragma once

#include <QDialog>

namespace Ui {
class sinkDialog;
}

class SinkDialog : public QDialog {
    Q_OBJECT

public:
    SinkDialog(QWidget* parent = nullptr);

    ~SinkDialog();

private slots:
    void on_btnOK_clicked();

    void on_btnCancel_clicked();

private:
    Ui::sinkDialog* ui;
};
