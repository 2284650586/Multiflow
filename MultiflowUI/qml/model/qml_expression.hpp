//
// Created by miku on 11/6/2023.
//

#pragma once

#include <MultiflowLibrary/expression/expression.hpp>

#include <QQmlContext>
#include <QString>

#include <memory>

struct QmlExpression {
    Q_GADGET
    Q_PROPERTY(QString name MEMBER _name CONSTANT)
    Q_PROPERTY(QString description MEMBER _description CONSTANT)

public:
    QString _name;
    QString _description;

    explicit QmlExpression(std::shared_ptr<ml::Expression> expression);
    QmlExpression() = default;

    std::shared_ptr<ml::Expression> _expression;
};

Q_DECLARE_METATYPE(QmlExpression)
