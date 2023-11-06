//
// Created by miku on 11/5/2023.
//

#include "subtract.hpp"

#include "math/math.hpp"

#include <vector>
#include <numeric>

namespace ml {
    Subtract::Subtract(std::vector<Expression> operands)
        : Expression("Subtract", "Subtract"), _operands(std::move(operands)) {}

    ml::Number Subtract::evaluate(const Environment &env) const {
        auto first = _operands.begin();
        Number firstValue = first->evaluate(env);
        return std::accumulate(
            ++first, _operands.end(),
            firstValue, [env] (Number acc, const Expression& v) {
                return ml::subtract(acc, v.evaluate(env));
            });
    }

    std::string Subtract::to_string() const {
        return join(_operands, " - ");
    }

    std::vector<Expression> Subtract::operands() const {
        return _operands;
    }
}
