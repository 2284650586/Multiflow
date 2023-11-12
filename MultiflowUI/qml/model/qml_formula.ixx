//
// Created by miku on 11/6/2023.
//

module;

#include "qml_formula.moc"
#include "qml_expression.hpp"

#include <spdlog/spdlog.h>

#include <QString>
#include <QVariant>
#include <string>

export module qml_formula;

import formula;

export struct QmlFormula {
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

    explicit QmlFormula(const ml::Formula& formula)
        : _formula(formula), _name(formula.name().c_str()),
          _description(formula.description().c_str()),
          _expression(formula.expression()),
          _lisp(formula.lisp().c_str()) {
        QSet<std::string> names;
        for (const auto& expression: formula.extractVariablesAndConstants()) {
            if (names.contains(expression->name())) {
                continue;
            }
            names.insert(expression->name());

            QmlExpression expressionWrapped{expression};
            if (expressionWrapped._isConstant) {
                spdlog::info("Adding constant: {}", expressionWrapped._name.toStdString());
                _constants.append(QVariant::fromValue(expressionWrapped));
            }
            if (expressionWrapped._isVariable) {
                spdlog::info("Adding variable: {}", expressionWrapped._name.toStdString());
                _variables.append(QVariant::fromValue(expressionWrapped));
            }
        }
    }
};

Q_DECLARE_METATYPE(QmlFormula)
