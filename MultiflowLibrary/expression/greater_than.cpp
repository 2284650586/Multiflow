//
// Created by miku on 11/9/2023.
//

#include "greater_than.hpp"

#include "math/math.hpp"

#include <utility>
#include <vector>
#include <format>

namespace ml
{
GreaterThan::GreaterThan(std::vector<std::shared_ptr<Expression>> operands)
    : Expression("GreaterThan", "GreaterThan"), _operands(std::move(operands)) {
    if (_operands.size() != 2) {
        throw MalformedExpressionException("GreaterThan must have exactly 2 operands");
    }
}

ml::Number GreaterThan::evaluate(const Environment &env) const {
    ml::Number x = _operands[0]->evaluate(env);
    ml::Number y = _operands[1]->evaluate(env);
    return ml::gt(x, y);
}

std::string GreaterThan::to_string() const {
    return std::format(
        "{} > {}", _operands[0]->to_string(), _operands[1]->to_string());
}

std::vector<std::shared_ptr<Expression>> GreaterThan::operands() const {
    return _operands;
}
}
