//
// Created by miku on 11/9/2023.
//

#include "equal_to.hpp"

#include "math/math.hpp"

#include <utility>
#include <vector>
#include <format>

namespace ml
{
EqualTo::EqualTo(std::vector<std::shared_ptr<Expression>> operands)
    : Expression("EqualTo", "EqualTo"), _operands(std::move(operands)) {
    if (_operands.size() != 2) {
        throw MalformedExpressionException("EqualTo must have exactly 2 operands");
    }
}

Number EqualTo::evaluate(const Environment &env) const {
    const Number x = _operands[0]->evaluate(env);
    const Number y = _operands[1]->evaluate(env);
    return eq(x, y);
}

std::string EqualTo::to_string() const {
    return std::format(
        "{} == {}", _operands[0]->to_string(), _operands[1]->to_string());
}

std::vector<std::shared_ptr<Expression>> EqualTo::operands() const {
    return _operands;
}
}
