//
// Created by miku on 11/5/2023.
//

#include "minus.hpp"

#include "math/math.hpp"

#include <utility>
#include <vector>
#include <format>

namespace ml
{
Minus::Minus(std::vector<std::shared_ptr<Expression>> operands)
    : Expression("Minus", "Minus"), _operands(std::move(operands)) {
    if (_operands.size() != 1) {
        throw MalformedExpressionException("Minus must have exactly 1 operand");
    }
}

Number Minus::evaluate(Environment& env) {
    const Number v = _operands[0]->evaluate(env);
    return subtract(0, v);
}

std::string Minus::representation() const {
    const auto& operandRepresentation = _operands[0]->representation();
    if (operandRepresentation.starts_with('-')) {
        return operandRepresentation.substr(1);
    }
    return "-" + operandRepresentation;
}

const std::vector<std::shared_ptr<Expression>>& Minus::operands() const {
    return _operands;
}
}
