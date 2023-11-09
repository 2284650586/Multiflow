//
// Created by miku on 11/9/2023.
//

#pragma once

#include <MultiflowLibrary/expression/expression.hpp>
#include <MultiflowLibrary/expression/variable.hpp>
#include <MultiflowLibrary/expression/constant.hpp>

#include "qml/interface/IQmlObject.hpp"
#include "qml/mixin/StaticConstructorMixin.hpp"

#include <QQmlContext>
#include <QString>
#include <QVariantList>

#include <memory>

struct QmlEnvironment: public QObject, public StaticConstructorMixin<QmlEnvironment>, public IQmlObject<QmlEnvironment> {
Q_OBJECT
 Q_PROPERTY(QVariantList variableNames READ variableNames WRITE setVariableNames)

public:
    friend class StaticConstructorMixin<QmlEnvironment>;

    explicit QmlEnvironment();

    [[nodiscard]]
    Q_INVOKABLE ml::Number get(const QString& name) const;

    Q_INVOKABLE void set(const QString& name, const ml::Number& value);

    Q_INVOKABLE void resetValues();

    [[nodiscard]]
    Q_INVOKABLE const QVariantList& variableNames() const;

    Q_INVOKABLE void setVariableNames(const QVariantList& variables);


    std::shared_ptr<ml::Environment> _environment;
    QVariantList _variables;
};
