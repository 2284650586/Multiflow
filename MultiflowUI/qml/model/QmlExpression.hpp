//
// Created by miku on 11/6/2023.
//

#pragma once

#include <MultiflowLibrary/expression/expression.hpp>

#include "QmlEnvironment.hpp"
#include "QmlResult.hpp"

#include <QQmlContext>
#include <QString>
#include <QVariantList>

#include <memory>

struct QmlExpression {
    Q_GADGET
    Q_PROPERTY(QString name MEMBER _name CONSTANT)
    Q_PROPERTY(QString description MEMBER _description CONSTANT)
    Q_PROPERTY(QString representation MEMBER _representation CONSTANT)
    Q_PROPERTY(bool isVariable MEMBER _isVariable CONSTANT)
    Q_PROPERTY(bool isConstant MEMBER _isConstant CONSTANT)
    Q_PROPERTY(ml::Number value MEMBER _value CONSTANT)

public:
    QString _name;
    QString _description;
    QString _representation;
    bool _isVariable = false;
    bool _isConstant = false;
    ml::Number _value = 0;

    explicit QmlExpression(std::shared_ptr<ml::Expression> expression);

    QmlExpression() = default;

    Q_INVOKABLE QmlResult evaluate(const QmlEnvironment* environment) const;

    std::shared_ptr<ml::Expression> _expression;
};

Q_DECLARE_METATYPE(QmlExpression)
