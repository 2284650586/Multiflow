//
// Created by miku on 11/6/2023.
//

#include "qml_expression.hpp"

#include <MultiflowLibrary/utils/type_utils.hpp>

QmlExpression::QmlExpression(std::shared_ptr<ml::Expression> expression)
    : _expression(std::move(expression)), _name(QString::fromStdString(expression->name())),
      _description(QString::fromStdString(expression->description())),
      _representation(QString::fromStdString(expression->to_string())) {
    _isConstant = ml::instance_of<ml::Constant>(_expression);
    _isVariable = ml::instance_of<ml::Variable>(_expression);

    if (_isConstant) {
        _value = std::dynamic_pointer_cast<ml::Constant>(_expression)->_value;
    }
}

ml::Number QmlExpression::evaluate(const QmlEnvironment* environment) const {
    return _expression->evaluate(*environment->_environment);
}
