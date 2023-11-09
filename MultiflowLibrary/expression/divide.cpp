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

    ml::Number Divide::evaluate(const Environment &env) const {
        auto first = _operands.begin();
        Number firstValue = first->get()->evaluate(env);
        return std::accumulate(
            ++first, _operands.end(),
            firstValue, [env] (Number acc, const std::shared_ptr<Expression>& v) {
                return ml::divide(acc, v->evaluate(env));
            });
    }

    std::string Divide::to_string() const {
        return joinExpression(_operands, " / ");
    }

    std::vector<std::shared_ptr<Expression>> Divide::operands() const {
        return _operands;
    }
}
