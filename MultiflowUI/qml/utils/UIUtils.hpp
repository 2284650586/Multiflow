//
// Created by miku on 2023/10/20.
//

#pragma once

#include <QString>
#include <QObject>

class UIUtils : public QObject {
    Q_OBJECT
public:
    explicit UIUtils(QObject *parent = nullptr);

    Q_INVOKABLE [[maybe_unused]] bool confirm(
        const QString& message,
        const QString& positiveButtonText,
        const QString& negativeButtonText
    );
};
