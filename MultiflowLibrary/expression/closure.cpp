//
// Created by miku on 11/16/2023.
//

#include "closure.hpp"

#include <utility>
#include <vector>

namespace ml
{
Closure::Closure(std::vector<std::shared_ptr<Expression>> operands)
    : Expression("Closure", "Closure"), _operands(std::move(operands)) {}

Number Closure::evaluate(Environment& env) {
    // Backup the environment.
    const Environment backup(env);

    // Empty closure evaluates to 0.
    Number result = 0;
    for (const auto& operand :_operands) {
        // Closure itself evaluates as the last operand.
        result = operand->evaluate(env);
    }

    // Restore the environment.
    env = backup;
    return result;
}

std::string Closure::representation() const {
    return joinExpression(_operands, ";\n");
}

const std::vector<std::shared_ptr<Expression>>& Closure::operands() const {
    return _operands;
}
}
