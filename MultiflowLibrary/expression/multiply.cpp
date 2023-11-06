//
// Created by miku on 11/5/2023.
//

#include "multiply.hpp"

#include "math/math.hpp"

#include <vector>
#include <numeric>

namespace ml {
    Multiply::Multiply(std::vector<Expression> operands)
        : Expression("Multiply", "Multiply"), _operands(std::move(operands)) {}

    ml::Number Multiply::evaluate(const Environment &env) const {
        return std::accumulate(
            _operands.begin(), _operands.end(),
            static_cast<ml::Number>(1), [env](Number acc, const Expression &v) {
                return ml::multiply(acc, v.evaluate(env));
            });
    }

    std::string Multiply::to_string() const {
        return join(_operands, " * ");
    }

    std::vector<Expression> Multiply::operands() const {
        return _operands;
    }
}
