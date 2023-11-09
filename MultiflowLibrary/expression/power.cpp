//
// Created by miku on 11/9/2023.
//

#include "power.hpp"

#include "math/math.hpp"

#include <utility>
#include <vector>
#include <format>

namespace ml
{
Power::Power(std::vector<std::shared_ptr<Expression>> operands)
    : Expression("Power", "Power"), _operands(std::move(operands)) {
    if (_operands.size() != 2) {
        throw MalformedExpressionException("Power must have exactly 2 operands");
    }
}

ml::Number Power::evaluate(const Environment &env) const {
    ml::Number x = _operands[0]->evaluate(env);
    ml::Number y = _operands[1]->evaluate(env);
    return ml::power(x, y);
}

std::string Power::to_string() const {
    return std::format(
        "({} ^ {})", _operands[0]->to_string(), _operands[1]->to_string());
}

std::vector<std::shared_ptr<Expression>> Power::operands() const {
    return _operands;
}
}
