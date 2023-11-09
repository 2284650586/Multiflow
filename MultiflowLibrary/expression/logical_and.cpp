//
// Created by miku on 11/9/2023.
//

#include "logical_and.hpp"

#include "math/math.hpp"

#include <utility>
#include <vector>

namespace ml {
LogicalAnd::LogicalAnd(std::vector<std::shared_ptr<Expression>> operands)
    : Expression("And", "And"), _operands(std::move(operands)) {}

ml::Number LogicalAnd::evaluate(const Environment& env) const {
    for (auto& operand: _operands) {
        if (ml::z(operand->evaluate(env))) {
            return 0;
        }
    }
    return 1;
}

std::string LogicalAnd::to_string() const {
    return joinExpression(_operands, " and ");
}

std::vector<std::shared_ptr<Expression>> LogicalAnd::operands() const {
    return _operands;
}
}
