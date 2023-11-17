//
// Created by miku on 11/6/2023.
//

#include "qml_formula.hpp"

#include <MultiflowLibrary/logging/logging.hpp>

QmlFormula::QmlFormula(const ml::Formula& formula)
    : _formula(formula), _name(formula.name().c_str()),
      _description(formula.description().c_str()),
      _expression(formula.expression()),
      _lisp(formula.lisp().c_str()) {
    QSet<std::string> names;
    for (const auto& expressions = formula.extractVariablesAndConstants();
         const auto& expression: expressions) {
        if (names.contains(expression->name())) {
            continue;
        }
        names.insert(expression->name());

        QmlExpression expressionWrapped{expression};
        if (expressionWrapped._isConstant) {
            _constants.append(QVariant::fromValue(expressionWrapped));
        }
        if (expressionWrapped._isVariable) {
            _variables.append(QVariant::fromValue(expressionWrapped));
        }
    }
}
