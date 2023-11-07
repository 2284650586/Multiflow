//
// Created by miku on 11/6/2023.
//

#pragma once

#include "qml_expression.hpp"

#include <QString>
#include <QQmlContext>

#include <MultiflowLibrary/formula/formula.hpp>

struct QmlFormula {
    Q_GADGET
    Q_PROPERTY(QString name MEMBER _name CONSTANT)
    Q_PROPERTY(QString description MEMBER _description CONSTANT)
    Q_PROPERTY(QmlExpression expression MEMBER _expression CONSTANT)

public:
    QString _name;
    QString _description;
    QmlExpression _expression;
    ml::Formula _formula;

    explicit QmlFormula(const ml::Formula& formula);
};

Q_DECLARE_METATYPE(QmlFormula)
