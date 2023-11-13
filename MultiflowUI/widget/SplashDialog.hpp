#pragma once

#include "ui_SplashDialog.h"

#include <QObject>
#include <QWidget>

class SplashDialog final : public QDialog {
    Q_OBJECT

public:
    static std::unique_ptr<SplashDialog> createAndShow();

private:
    explicit SplashDialog(QWidget* parent = nullptr);

signals:

public slots:
    void updateStatus(QString statusMessage);

private:
    Ui::SplashDialog* ui;
    QString _statusMessage;
};
