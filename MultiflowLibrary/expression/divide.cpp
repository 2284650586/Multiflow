//
// Created by miku on 11/5/2023.
//

#include "divide.hpp"

#include "math/math.hpp"

#include <utility>
#include <vector>
#include <numeric>

namespace ml
{
    Divide::Divide(std::vector<std::shared_ptr<Expression>> operands)
        : Expression("Divide", "Divide"), _operands(std::move(operands)) {}

Number Divide::evaluate(const Environment &env) const {
        auto first = _operands.begin();
        const Number firstValue = first->get()->evaluate(env);
        return std::accumulate(
            ++first, _operands.end(),
            firstValue, [env] (const Number acc, const std::shared_ptr<Expression>& v) {
                return divide(acc, v->evaluate(env));
            });
    }

    std::string Divide::representation() const {
        return joinExpression(_operands, " / ");
    }

    const std::vector<std::shared_ptr<Expression>>& Divide::operands() const {
        return _operands;
    }
}
