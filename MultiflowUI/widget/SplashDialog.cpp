#include "SplashDialog.hpp"

SplashDialog::SplashDialog(QWidget* parent)
    : QDialog{parent}, ui(new Ui::SplashDialog) {
    ui->setupUi(this);
    setWindowFlags(Qt::WindowTitleHint);
}

std::unique_ptr<SplashDialog> SplashDialog::createAndShow() {
    auto instance = std::unique_ptr<SplashDialog>(new SplashDialog());
    instance->show();
    QApplication::processEvents();
    return instance;
}

void SplashDialog::updateStatus(QString statusMessage) {
    _statusMessage = std::move(statusMessage);
    ui->labelStatusMessage->setText(_statusMessage);
    QApplication::processEvents();
}
