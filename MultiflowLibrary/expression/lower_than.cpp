//
// Created by miku on 11/9/2023.
//

#include "lower_than.hpp"

#include "math/math.hpp"

#include <utility>
#include <vector>
#include <format>

namespace ml
{
LowerThan::LowerThan(std::vector<std::shared_ptr<Expression>> operands)
    : Expression("LowerThan", "LowerThan"), _operands(std::move(operands)) {
    if (_operands.size() != 2) {
        throw MalformedExpressionException("LowerThan must have exactly 2 operands");
    }
}

Number LowerThan::evaluate(const Environment &env) const {
    const Number x = _operands[0]->evaluate(env);
    const Number y = _operands[1]->evaluate(env);
    return lt(x, y);
}

std::string LowerThan::representation() const {
    return std::format(
        "{} < {}", _operands[0]->representation(), _operands[1]->representation());
}

std::vector<std::shared_ptr<Expression>> LowerThan::operands() const {
    return _operands;
}
}
