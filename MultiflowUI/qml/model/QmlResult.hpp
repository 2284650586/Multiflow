//
// Created by miku on 11/9/2023.
//

#pragma once

#include <QObject>
#include <QString>

#include <MultiflowLibrary/expression/expression.hpp>

struct QmlResult {
Q_GADGET
Q_PROPERTY(QString message MEMBER _message CONSTANT)
Q_PROPERTY(bool success MEMBER _success CONSTANT)
Q_PROPERTY(ml::Number value MEMBER _value CONSTANT)

public:
    QString _message;
    bool _success = false;
    ml::Number _value = 0;

    static QmlResult success(ml::Number value);
    static QmlResult failure(QString message);

    QmlResult(QString message, bool success, ml::Number value);
    QmlResult() = default;

    [[nodiscard]]
    const QString& message() const;

    [[nodiscard]]
    bool success() const;

    [[nodiscard]]
    ml::Number value() const;
};

Q_DECLARE_METATYPE(QmlResult)
