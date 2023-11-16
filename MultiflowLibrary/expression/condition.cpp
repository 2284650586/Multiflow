//
// Created by miku on 11/9/2023.
//

#include "condition.hpp"

#include "math/math.hpp"

#include <utility>
#include <vector>
#include <format>
#include <sstream>

namespace ml
{

// (if v1 cond1 v2 cond2 v3)
Condition::Condition(std::vector<std::shared_ptr<Expression>> operands)
    : Expression("Piecewise", "Piecewise"), _operands(std::move(operands)) {
    if ((_operands.size() & 1) == 0 || _operands.size() < 2) {
        throw MalformedExpressionException("Arguments for Piecewise must be odd and at least 3");
    }
}

Number Condition::evaluate(const Environment &env) const {
    for (int i = 0; i < _operands.size() - 1; i += 2) {
        if (is_logical_true(_operands[i + 1]->evaluate(env))) {
            return _operands[i]->evaluate(env);
        }
    }
    return _operands[_operands.size() - 1]->evaluate(env);
}

std::string Condition::representation() const {
    std::stringstream ss;
    for (int i = 0; i < _operands.size() - 1; i += 2) {
        ss << _operands[i]->representation() << " (" << _operands[i + 1]->representation() << ")\n";
    }
    ss << _operands[_operands.size() - 1]->representation() << " (Else)";
    return ss.str();
}

const std::vector<std::shared_ptr<Expression>>& Condition::operands() const {
    return _operands;
}
}
