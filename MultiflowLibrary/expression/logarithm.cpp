//
// Created by miku on 11/9/2023.
//

#include "logarithm.hpp"

#include "math/math.hpp"

#include <utility>
#include <vector>
#include <format>

namespace ml
{
Logarithm::Logarithm(std::vector<std::shared_ptr<Expression>> operands)
    : Expression("Log", "Log"), _operands(std::move(operands)) {
    if (_operands.size() != 2) {
        throw MalformedExpressionException("Logarithm must have exactly 2 operands");
    }
}

Number Logarithm::evaluate(const Environment &env) const {
    const Number x = _operands[0]->evaluate(env);
    const Number y = _operands[1]->evaluate(env);
    return logarithm(x, y);
}

std::string Logarithm::representation() const {
    return std::format(
        "log({}, {})", _operands[0]->representation(), _operands[1]->representation());
}

std::vector<std::shared_ptr<Expression>> Logarithm::operands() const {
    return _operands;
}
}
