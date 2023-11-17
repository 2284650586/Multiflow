//
// Created by miku on 11/5/2023.
//

#include "subtract.hpp"

#include "math/math.hpp"

#include <utility>
#include <vector>
#include <numeric>

namespace ml {
Subtract::Subtract(std::vector<std::shared_ptr<Expression>> operands)
    : Expression("Subtract", "Subtract"), _operands(std::move(operands)) {
}

Number Subtract::evaluate(Environment& env) {
    auto first = _operands.begin();
    const Number firstValue = first->get()->evaluate(env);
    return std::accumulate(
        ++first, _operands.end(),
        firstValue, [&env](const Number acc, const std::shared_ptr<Expression>& v) {
            return subtract(acc, v->evaluate(env));
        });
}

std::string Subtract::representation() const {
    return joinExpression(_operands, " - ");
}

const std::vector<std::shared_ptr<Expression>>& Subtract::operands() const {
    return _operands;
}
}
