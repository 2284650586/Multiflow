//
// Created by miku on 11/9/2023.
//

#pragma once

#include <MultiflowLibrary/expression/expression.hpp>

#include "qml/interface/IQmlObject.hpp"
#include "qml/mixin/StaticConstructorMixin.hpp"

#include <QQmlContext>
#include <QString>
#include <QVariantList>

#include <memory>

// QmlEnvironment can not be final - Qt internally subclasses it.
// NOLINTNEXTLINE
struct QmlEnvironment : QObject, StaticConstructorMixin<QmlEnvironment>, IQmlObject<QmlEnvironment> {
    Q_OBJECT
    Q_PROPERTY(QVariantList variableNames READ variableNames WRITE setVariableNames)

public:
    friend class StaticConstructorMixin;

    explicit QmlEnvironment();

    [[nodiscard]]
    Q_INVOKABLE ml::Number get(const QString& name) const;

    Q_INVOKABLE void set(const QString& name, const ml::Number& value) const;

    Q_INVOKABLE void resetValues();

    [[nodiscard]]
    Q_INVOKABLE const QVariantList& variableNames() const;

    Q_INVOKABLE void setVariableNames(const QVariantList& variables);


    std::shared_ptr<ml::Environment> _environment;
    QVariantList _variables;
};
