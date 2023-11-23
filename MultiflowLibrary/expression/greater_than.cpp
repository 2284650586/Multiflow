//
// Created by miku on 11/9/2023.
//

#include "greater_than.hpp"

#include "math/math.hpp"

#include <utility>
#include <vector>
#include <fmt/core.h>

namespace ml {
GreaterThan::GreaterThan(std::vector<std::shared_ptr<Expression>> operands)
    : Expression("GreaterThan", "GreaterThan"), _operands(std::move(operands)) {
    if (_operands.size() != 2) {
        throw MalformedExpressionException("GreaterThan must have exactly 2 operands");
    }
}

Number GreaterThan::evaluate(Environment& env) {
    const Number x = _operands[0]->evaluate(env);
    const Number y = _operands[1]->evaluate(env);
    return gt(x, y);
}

std::string GreaterThan::representation() const {
    return fmt::format(
        "{} > {}", _operands[0]->representation(), _operands[1]->representation());
}

const std::vector<std::shared_ptr<Expression>>& GreaterThan::operands() const {
    return _operands;
}
}
