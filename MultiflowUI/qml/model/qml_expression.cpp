//
// Created by miku on 11/6/2023.
//

#include "qml_expression.hpp"

QmlExpression::QmlExpression(std::shared_ptr<ml::Expression> expression)
    : _expression(std::move(expression)), _name(QString::fromStdString(expression->name())),
      _description(QString::fromStdString(expression->description())) {
}
