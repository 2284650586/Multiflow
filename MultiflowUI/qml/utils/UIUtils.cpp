//
// Created by miku on 2023/10/20.
//

#include "UIUtils.hpp"

#include <QMessageBox>
#include <QPushButton>

#include "shared.hpp"
#include "constants.hpp"

UIUtils::UIUtils(QObject* parent)
    : QObject(parent), IQmlSingleton("Multiflow.UI", 1, 0, "UIUtils") {
}

[[maybe_unused]] bool
UIUtils::confirm(const QString& message, const QString& positiveButtonText, const QString& negativeButtonText) {
    auto dialog = QMessageBox();
    dialog.setWindowTitle(AppName);
    dialog.setText(message);
    dialog.addButton(negativeButtonText, QMessageBox::RejectRole);
    dialog.setIcon(QMessageBox::Question);
    const auto buttonPositive = dialog.addButton(positiveButtonText, QMessageBox::AcceptRole);
    dialog.exec();
    return dialog.clickedButton() == buttonPositive;
}

[[maybe_unused]] void
UIUtils::error(const QString& message, const QString& positiveButtonText) {
    auto dialog = QMessageBox();
    dialog.setWindowTitle(AppName);
    dialog.setText(message);
    dialog.addButton(positiveButtonText, QMessageBox::AcceptRole);
    dialog.setIcon(QMessageBox::Critical);
    dialog.exec();
}
