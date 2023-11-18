//
// Created by miku on 11/6/2023.
//

#pragma once

#include "QmlExpression.hpp"

#include <QString>
#include <QQmlContext>
#include <QVariantList>

#include <MultiflowLibrary/formula/formula.hpp>

struct QmlFormula {
    Q_GADGET
    Q_PROPERTY(QString name MEMBER _name CONSTANT)
    Q_PROPERTY(QString description MEMBER _description CONSTANT)
    Q_PROPERTY(QString lisp MEMBER _lisp CONSTANT)
    Q_PROPERTY(QmlExpression expression MEMBER _expression CONSTANT)
    Q_PROPERTY(QVariantList variables MEMBER _variables CONSTANT)
    Q_PROPERTY(QVariantList constants MEMBER _constants CONSTANT)

public:
    QString _name;
    QString _description;
    QString _lisp;
    QmlExpression _expression;
    ml::Formula _formula;
    QVariantList _variables;
    QVariantList _constants;

    explicit QmlFormula(const ml::Formula& formula);
};

Q_DECLARE_METATYPE(QmlFormula)
