//
// Created by miku on 11/9/2023.
//

#include "logical_or.hpp"

#include "math/math.hpp"

#include <utility>
#include <vector>

namespace ml {
LogicalOr::LogicalOr(std::vector<std::shared_ptr<Expression>> operands)
    : Expression("Or", "Or"), _operands(std::move(operands)) {}

Number LogicalOr::evaluate(const Environment& env) const {
    for (auto& operand: _operands) {
        if (!z(operand->evaluate(env))) {
            return 1;
        }
    }
    return 0;
}

std::string LogicalOr::to_string() const {
    return joinExpression(_operands, " or ");
}

std::vector<std::shared_ptr<Expression>> LogicalOr::operands() const {
    return _operands;
}
}
