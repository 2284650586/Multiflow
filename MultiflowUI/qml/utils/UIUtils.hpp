//
// Created by miku on 2023/10/20.
//

#pragma once

#include <QString>
#include <QObject>

#include "qml/mixin/SingletonMixin.hpp"
#include "qml/interface/IQmlSingleton.hpp"

class UIUtils final : public QObject, public SingletonMixin<UIUtils>, public IQmlSingleton<UIUtils> {
    Q_OBJECT

    friend class SingletonMixin;

public:
    /**
     * @return true if positive button is clicked, false otherwise
     */
    Q_INVOKABLE [[maybe_unused]] static bool confirm(
        const QString& message,
        const QString& positiveButtonText,
        const QString& negativeButtonText
    );

    Q_INVOKABLE [[maybe_unused]] static void error(
        const QString& message,
        const QString& positiveButtonText
    );

private:
    explicit UIUtils(QObject* parent = nullptr);
};
