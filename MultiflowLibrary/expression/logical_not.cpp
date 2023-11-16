//
// Created by miku on 11/9/2023.
//

#include "logical_not.hpp"

#include "math/math.hpp"

#include <utility>
#include <vector>
#include <format>

namespace ml {
LogicalNot::LogicalNot(std::vector<std::shared_ptr<Expression>> operands)
    : Expression("Not", "Not"), _operands(std::move(operands)) {
    if (_operands.size() != 1) {
        throw MalformedExpressionException("Logical Not must have exactly 1 operand");
    }
}

Number LogicalNot::evaluate(const Environment& env) const {
    const Number v = _operands[0]->evaluate(env);
    return is_logical_true(v) ? FALSE : TRUE;
}

std::string LogicalNot::representation() const {
    return std::format("(not {})", _operands[0]->representation());
}

const std::vector<std::shared_ptr<Expression>>& LogicalNot::operands() const {
    return _operands;
}
}
